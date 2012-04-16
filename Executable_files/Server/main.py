# coding=UTF-8
from socket import *
from select import select
from lib.Initialization import start
from lib.Communication import przetworz
from lib.Classes import rekord

serv,klienci,db=start()

while True:
    try:
        inputready,outputready,exceptready = select([serv] + [x.socket for x in klienci], (), (), 4)
    except:
        # ktores gniazdo umarlo straszna smiercia.
        # wykrywanie polega na selectowaniu kazdego z osobna i ten ktory rzuci wyjatek to ten zly
     
        for klient in klienci:
            try:
               select((klient.socket, ), (), (), 0)
            except: # mam cie uszkodzone polaczenie
                klienci.remove(klient)
                for x in klienci:
                    try:
                        x.sock.send("WylogowanoUser\1"+klient.login+"\2")
                    except:
                        pass
    else:
        # wszystko poszlo dobrze. Teraz sprawdzamy wszystkich...
        for sock in inputready:
            if sock == serv:        # jesli mozemy czytac gniazdo serwera to znaczy ze jest nowe polaczenie
                nowysock, adres = serv.accept()
                rekordklient=rekord()
                rekordklient.socket=nowysock
                rekordklient.id=-1;
                klienci.append(rekordklient)
                #nowysock.send('Ohayo!\n')
            else:                   # to zwykly klient. Odbierzmy dane i wyslijmy je innym
                try:
                    dane = sock.recv(1024)  # jesli gniazdo jest czytalne(w mysl select) to recv() na pewno COS zwroci...
                    dane=dane.decode('utf-8')
                    przetworz(dane,db,sock,klienci)
                except:     # ten wyjatek bedzie rzucany ekstremalnie rzadko, ale piszemy kuloodpornie
                    dane = ''       # zasymulujmy ze koniec polaczenia
               
                if dane == '':      # jesli recv zwraca puste to koniec polaczenia!
                    for rek in klienci:
                        if rek.socket==sock:
                            for x in klienci:
                                try:
                                    x.socket.send("WylogowanoUser\1"+rek.login+"\2")
                                except:
                                    pass
                            klienci.remove(rek)
                    continue
                   
                # rozsylamy do wszystkich
                #for klient in klienci:
                #   try:
                #        klient.socket.send(dane)
                #    except:
                #        pass    # ten socket jest bledny, ale dojdziemy go przy nastepnym obrocie selecta
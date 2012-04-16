# coding=UTF-8
import MySQLdb
from lepl.apps.rfc3696 import Email
def przetworz(dane,db,sock,klienci):
    podzielone=dane.split('\1')
    c=db.cursor()
    for x in klienci:
        if x.socket==sock:
            klient=x
    if klient.id==-1:
        if podzielone[0]=="Reg":
            if(podzielone[1].find(" ")!=-1):
                try:
                    sock.send("Błąd\1Login nie może zawierać spacji\2")
                except:
                    pass
            else:
                if (len(podzielone[1])<1) & (len(podzielone[1])>50):
                    try:
                        sock.send("Błąd\1Login musi mieć minimum 1 znak maksimum 50 znaków\2")
                    except:
                        pass
                else:
                    c.execute("""SELECT login FROM users WHERE login=%s""",(podzielone[1],))
                    if c.rowcount>0:
                        try:
                            sock.send("Błąd\1Podany login jest zajęty\2")
                        except:
                            pass
                    else:
                        if (len(podzielone[2])<6) & (len(podzielone[2])>50):
                            try:
                                sock.send("Błąd\1Hasło musi mieć minimum 6 znaków maksymalnie 50 znakow\2")
                            except:
                                pass
                        else:
                            validatorEmail=Email();
                            if(validatorEmail(podzielone[3])==False):
                                try:
                                    sock.send("Błąd\1Format adresu email jest niepoprawny\2")
                                except:
                                    pass
                            else:
                                c.execute("""SELECT email FROM users WHERE email=%s""",(podzielone[3],))
                                if c.rowcount>0:
                                    try:
                                        sock.send("Błąd\1Ktoś inny używa tego emaila\2")
                                    except:
                                        pass
                                else: 
                                    c.execute("""INSERT INTO users (login,password,email) VALUES (%s, %s, %s)""",(podzielone[1],podzielone[2],podzielone[3],))
                                    db.commit()
                                    try:
                                        sock.send("Sukcess\1Zarejstrowano pomyślnie\2")
                                    except:
                                        pass
        if podzielone[0]=="Log":
            c.execute("""SELECT id,login,password FROM users WHERE (login=%s) AND (password=%s)""",(podzielone[1],podzielone[2]))
            if c.rowcount==0:
                try:
                    sock.send("Błąd\1Hasło nie zgadza się z loginem\nlub login nie istnieje\2")
                except:
                    pass
            else:
                id,login,haslo=c.fetchone()
                klient.id=id
                klient.login=login
                
                for x in klienci:
                    try:
                        sock.send(("NowyUser\1"+x.login+"\2").encode('utf-8'))
                    except:
                        pass
                    if x.id!=id:
                        try:
                           x.socket.send(("NowyUser\1"+login+"\2").encode('utf-8'))
                        except:
                            pass
                try:        
                    sock.send("Sukcess\1Zalogowano pomyślnie\2")
                except:
                    pass
    if klient.id!=-1:
        if podzielone[0]=="/all":
            for x in klienci:
                try:
                    x.socket.send((podzielone[0]+"\1"+klient.login+"\1"+podzielone[1]+"\2").encode('utf-8'))
                except:
                    pass
        if podzielone[0]=="/pm":
            znal=False
            for x in klienci:
                if x.login==podzielone[1]:
                    znal=True
                    try:
                        x.socket.send((podzielone[0]+"\1"+klient.login+"\1"+podzielone[2]+"\2").encode('utf-8'))
                        klient.socket.send((podzielone[0]+"\1"+klient.login+"\1"+podzielone[2]+"\2").encode('utf-8'))
                    except:
                        pass
            if znal==False:
                try:
                    klient.socket.send("Brak Usera\2")
                except:
                    pass
            
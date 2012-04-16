# coding=UTF-8
from socket import *
from ConfigParser import SafeConfigParser
import MySQLdb
def start():
    #wczytanie danych z pliku cfg
    print('Initialization server')
    parser = SafeConfigParser()
    parser.read('config.cfg')
    port=int(parser.get('server', 'port'))
    ip=parser.get('server', 'ip')
    host1=parser.get('mysql', 'host')
    user1=parser.get('mysql', 'user')
    passwd1=parser.get('mysql', 'password')
    db1=parser.get('mysql', 'db')
    print 'ip: '+ip
    print 'port: '+str(port)
    #ustawienie serwera
    serv=socket(AF_INET, SOCK_STREAM)
    serv.bind((ip, port))
    serv.listen(10)
    klienci = []
    
    #polaczenie z baza mysql 
    db=MySQLdb.connect(host=host1,user=user1,passwd=passwd1,db=db1)
    c=db.cursor()
    print 'Connected to database'
    #utworzenie tabeli jesli nie istenieje
    c.execute("""CREATE TABLE IF NOT EXISTS `users` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `login` varchar(255) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `password` varchar(255) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `email` varchar(255) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `admin` tinyint(1) NOT NULL DEFAULT '0',
  `ban` tinyint(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE utf8_bin AUTO_INCREMENT=1 """)
    print 'Created tables in database'
    print 'Server is runing correctly'
    
    return serv,klienci,db
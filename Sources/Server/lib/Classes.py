# coding=UTF-8
import MySQLdb

class rekord():
    pass

class DB:
  conn = None
  server = None
  database = None
  username = None
  pswd = None
  
  def connect(self,server, database, username, pswd):
    self.server=server
    self.database=database
    self.username=username
    self.pswd=pswd
    self.conn = MySQLdb.connect(host=self.server,user=self.username,passwd=self.pswd,db=self.database,use_unicode=True, charset="utf8")
    
  def reconnect(self):
    self.conn = MySQLdb.connect(host=self.server,user=self.username,passwd=self.pswd,db=self.database,use_unicode=True, charset="utf8")

  def query(self, sql,parametry=()):
    try:
      cursor = self.conn.cursor()
      cursor.execute(sql,parametry)
    except (AttributeError, MySQLdb.OperationalError):
      self.reconnect()
      cursor = self.conn.cursor()
      cursor.execute(sql,parametry)
    return cursor
    

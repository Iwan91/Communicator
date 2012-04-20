# coding=UTF-8
import MySQLdb

class rekord():
    pass

class DB:
  conn = None
      
  def connect(self,server, database, username, pswd):
    self.conn = MySQLdb.connect(host=server,user=username,passwd=pswd,db=database,use_unicode=True, charset="utf8")

  def query(self, sql,parametry=()):
    try:
      cursor = self.conn.cursor()
      cursor.execute(sql,parametry)
    except (AttributeError, MySQLdb.OperationalError):
      self.connect()
      cursor = self.conn.cursor()
      cursor.execute(sql,parametry)
    return cursor
    

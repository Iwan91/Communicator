//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "sha1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;
String bufor;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::wyslij(String dane)
{
Debug->Lines->Add("Wysy³am: "+dane);
ClientSocket1->Socket->SendText(AnsiToUtf8(dane));
}
//------------------------------------------
std::vector<String> TForm1::podziel(String dane,char sep)
{
        int i;
        String tym="";
        std::vector<String> v;
        for (i=1;i<=dane.Length();i++)
        {
                if(dane[i]!=sep)
                {
                tym=tym+dane[i];
                }
                else
                {
                v.push_back(tym);
                tym="";    
                }  
        }
        v.push_back(tym);
        return v;
}
//----------------------------------------------
String TForm1::Bufor()
{  
 int found;
 String rozkaz="";
 found=bufor.Pos('\2');
 if(found!=0)
 {
 rozkaz=bufor.SubString(1,found-1);
 bufor.Delete(1,found);
 }
 return rozkaz;
}
//----------------------------------------------
void __fastcall TForm1::ClientSocket1Read(TObject *Sender,
      TCustomWinSocket *Socket)
{
String msg=Utf8ToAnsi(Socket->ReceiveText());
String komenda;
Debug->Lines->Add("Otrzymalem: "+msg);
bufor=bufor+msg;
Debug->Lines->Add("Bufor: "+bufor);

while((komenda=Bufor())!="")
{
Debug->Lines->Add("Wykonuje: "+komenda);
std::vector <String> pociete=podziel(komenda,'\1');

if(pociete[0]=="B³¹d") ShowMessage(pociete[1]);
if(pociete[0]=="Sukcess")
{

        if(pociete[1]=="Zalogowano pomyœlnie")
        {
          GroupBox1->Visible=false;
          GroupBox3->Visible=true;
          Memo1->Lines->Add("*** Zalogowano jako: "+Edit1->Text+" ***");
        }
        if(pociete[1]=="Zarejstrowano pomyœlnie")
        {
         ShowMessage(pociete[1]);
         GroupBox2->Visible=false;
         GroupBox1->Visible=true;
        }
}
if(pociete[0]=="/all") Memo1->Lines->Add("<"+pociete[1]+">"+pociete[2]);
if(pociete[0]=="NowyUser") ListBox1->Items->Add(pociete[1]);
if(pociete[0]=="WylogowanoUser")
{
        for (int i=0;i<ListBox1->Items->Count;i++)
        {
                if(ListBox1->Items->Strings[i]==pociete[1]) ListBox1->Items->Delete(i);
        }
}

if(pociete[0]=="Brak Usera") Memo1->Lines->Add("*** U¿ytkownik nie jest zalogowany. Niedostarczono wiadomoœci ***");
if(pociete[0]=="/pm") Memo1->Lines->Add("Szept<"+pociete[1]+">"+pociete[2]);
}

}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
 int port=0;
 String address="";
 AnsiString nazwaPliku = ExtractFilePath( Application->ExeName ) + "config.cfg";
 TIniFile *config = new TIniFile(nazwaPliku);
 port=config->ReadInteger("server", "port", 5000);
 address=config->ReadString("server", "address", "127.0.0.1");
 delete config;

 Debug->Lines->Add(IntToStr(port));
 Debug->Lines->Add(address);

 ClientSocket1->Address=address;
 ClientSocket1->Port=port;

 ClientSocket1->Active=true;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::BitBtn2Click(TObject *Sender)
{
GroupBox1->Visible=false;
GroupBox2->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn3Click(TObject *Sender)
{
        if( Edit2->Text=="" && Edit3->Text=="" && MaskEdit2->Text=="" && MaskEdit3->Text=="")
        {
                ShowMessage("Wype³nij wszystkie pola");
        }
        else
        {
                if(MaskEdit2->Text!=MaskEdit3->Text)
                {
                ShowMessage("Wpisane has³a siê nie zgadzaj¹");
                }
                else
                {
                            String login,haslo,email;
                            unsigned char hash[20];
                            char hexstring[41];
                            login=Edit2->Text;
                            haslo=MaskEdit2->Text;
                            email=Edit3->Text;
                            sha1::calc(haslo.c_str(),haslo.Length(),hash);
                            sha1::toHexString(hash, hexstring);
                            Application->ProcessMessages();
                            wyslij("Reg\1"+login+"\1"+hexstring+"\1"+email);
                }
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ClientSocket1Error(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
ShowMessage("B³¹d po³¹czenia z serwerem: "+IntToStr(ErrorCode)+"\nAplikacja zostanie zamkniêta");
Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
wyslij("");
ClientSocket1->Active=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
 String login,haslo;
 login=Edit1->Text;
 haslo=MaskEdit1->Text;
 unsigned char hash[20];
 char hexstring[41];
 sha1::calc(haslo.c_str(),haslo.Length(),hash);
 sha1::toHexString(hash, hexstring);
 wyslij("Log\1"+login+"\1"+hexstring);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BitBtn4Click(TObject *Sender)
{
        if(Edit4->Text!="")
        {
        std::vector <String> pociete=podziel(Edit4->Text,' ');
        if(pociete[0]=="/all") wyslij("/all\1"+Edit4->Text.SubString(6,Edit4->Text.Length()));
        else
        {
                if(pociete[0]=="/pm")
                {
                        if(pociete.size()>2)
                        {
                        wyslij("/pm\1"+pociete[1]+"\1"+Edit4->Text.SubString(6+pociete[1].Length(),Edit4->Text.Length()));
                        }
                }
                
        else wyslij("/all\1"+Edit4->Text);
        }
        Edit4->Text="";
        }

}
//---------------------------------------------------------------------------




int wybrany;
void __fastcall TForm1::ListBox1ContextPopup(TObject *Sender,
      TPoint &MousePos, bool &Handled)
{
wybrany=-1;
wybrany=ListBox1->ItemAtPos(MousePos, true);
if(wybrany!=-1)
{
ListBox1->ItemIndex=wybrany;
PopupMenu1->Popup(ListBox1->Left+Form1->Left+MousePos.x,ListBox1->Top+Form1->Top+MousePos.y+40);
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Szept1Click(TObject *Sender)
{
Edit4->Text="/pm "+ListBox1->Items->Strings[wybrany]+" ";
}
//---------------------------------------------------------------------------




void __fastcall TForm1::Edit4KeyPress(TObject *Sender, char &Key)
{
if(Key==VK_RETURN)
{
Key = 0;
BitBtn4->Click();
}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::MaskEdit1KeyPress(TObject *Sender, char &Key)
{
if(Key==VK_RETURN)
{
Key = 0;
BitBtn1->Click();
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn5Click(TObject *Sender)
{
GroupBox2->Visible=false;
GroupBox1->Visible=true;
}
//---------------------------------------------------------------------------


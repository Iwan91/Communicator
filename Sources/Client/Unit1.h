//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ScktComp.hpp>
#include <inifiles.hpp>
#include <Buttons.hpp>
#include <Mask.hpp>
#include <Menus.hpp>
#include <vector>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TClientSocket *ClientSocket1;
        TMemo *Debug;
        TGroupBox *GroupBox1;
        TEdit *Edit1;
        TLabel *Label1;
        TMaskEdit *MaskEdit1;
        TLabel *Label2;
        TBitBtn *BitBtn1;
        TLabel *Label3;
        TBitBtn *BitBtn2;
        TGroupBox *GroupBox2;
        TEdit *Edit2;
        TEdit *Edit3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TMaskEdit *MaskEdit2;
        TMaskEdit *MaskEdit3;
        TBitBtn *BitBtn3;
        TGroupBox *GroupBox3;
        TEdit *Edit4;
        TBitBtn *BitBtn4;
        TMemo *Memo1;
        TListBox *ListBox1;
        TLabel *Label8;
        TLabel *Label9;
        TPopupMenu *PopupMenu1;
        TMenuItem *Szept1;
        void __fastcall ClientSocket1Read(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall ClientSocket1Error(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall BitBtn4Click(TObject *Sender);
        void __fastcall ListBox1ContextPopup(TObject *Sender,
          TPoint &MousePos, bool &Handled);
        void __fastcall Szept1Click(TObject *Sender);
        void __fastcall Edit4KeyPress(TObject *Sender, char &Key);

private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        void __fastcall wyslij(String dane);
        std::vector<String> podziel(String dane,char sep);
        String Bufor();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

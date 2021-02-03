#pragma once

#include <stdint.h>

#include <unordered_map>

#include "QuickDrawFormats.hh" // for Rect, Color

struct Queue {
  uint16_t flags;
  uint32_t head;
  uint32_t tail;
} __attribute__((packed));

struct SystemParameters {
  uint8_t SPValid;
  uint8_t SPATalkA;
  uint8_t SPATalkB;
  uint8_t SPConfig;
  uint16_t SPPortA;
  uint16_t SPPortB;
  uint32_t SPAlarm;
  uint16_t SPFont;
  uint8_t SPKbd;
  uint8_t SPPrint;
  uint8_t SPVolCtl;
  uint8_t SPClikCaret;
  uint8_t SPMisc1;
  union {
    uint8_t SPMisc2;
    uint8_t PCDeskPat;
  };
} __attribute__((packed));

struct LowMemoryGlobals {
  // 0000
  uint32_t __m68k_reset_stack__;
  uint32_t __m68k_vec_reset__;
  uint32_t BusErrVct;
  uint32_t __m68k_vec_address_error__;
  // 0010
  uint32_t __m68k_vec_illegal__;
  uint32_t __m68k_vec_div_zero__;
  uint32_t __m68k_vec_chk__;
  uint32_t __m68k_vec_trapv__;
  // 0020
  uint32_t __m68k_vec_priv_violation__;
  uint32_t __m68k_vec_trace__;
  uint32_t __m68k_vec_a_trap__;
  uint32_t __m68k_vec_f_trap__;
  // 0030
  uint32_t unused1[3];
  uint32_t __m68k_vec_uninitialized__;
  uint32_t unused2[8];
  // 0060
  uint32_t __m68k_vec_spurious__;
  uint32_t __m68k_vec_via__;
  uint32_t __m68k_vec_scc__;
  uint32_t __m68k_vec_via_scc__;
  // 0070
  uint32_t __m68k_vec_switch__;
  uint32_t __m68k_vec_switch_via__;
  uint32_t __m68k_vec_switch_scc__;
  uint32_t __m68k_vec_switch_via_scc__;
  // 0080
  uint8_t unused3[0x80];
  // 0100
  int16_t MonkeyLives;
  uint16_t ScrVRes;
  uint16_t ScrHRes;
  uint16_t ScreenRow;
  uint32_t MemTop;
  uint32_t BufPtr;
  // 0110
  uint32_t StkLowPt;
  uint32_t HeapEnd;
  uint32_t TheZone;
  uint32_t UTableBase;
  // 0120
  uint32_t MacJump;
  uint32_t DskRtnAdr;
  uint32_t PollRtnAdr;
  uint8_t DskVerify;
  uint8_t LoadTrap;
  uint8_t MmInOK;
  uint8_t CPUFlag;
  // 0130
  uint32_t ApplLimit;
  uint32_t SonyVars;
  uint16_t PWMValue;
  uint32_t PollStack;
  // 013E
  uint32_t PollProc;
  int16_t DskErr;
  uint16_t SysEvtMask;
  uint32_t SysEvtBuf;
  Queue EventQueue;
  // 0154
  uint16_t EvtBufCnt;
  uint32_t RndSeed;
  uint16_t SysVersion;
  uint8_t SEvtEnb;
  uint8_t DSWndUpdate;
  uint8_t FontFlag;
  uint8_t IntFlag;
  // 0160
  Queue VBLQueue;
  uint32_t Ticks;
  uint32_t MBTicks;
  // 0172
  uint8_t MBState;
  uint8_t Tocks;
  uint64_t KeyMap;
  uint32_t KeypadMap;
  // 0180
  uint32_t unused4;
  uint16_t KeyLast;
  uint32_t KeyTime;
  uint32_t KeyRepTime;
  uint16_t KeyThresh;
  // 0190
  uint16_t KeyRepThresh;
  // 0192
  uint32_t Lvl1DT[8]; // TODO: type is probably wrong here
  // 01B2
  uint32_t Lvl2DT[8]; // TODO: type is probably wrong here
  // 01D2
  uint16_t UnitNtryCnt;
  uint32_t VIA;
  uint32_t SCCRd;
  uint32_t SCCWr;
  // 01E0
  uint32_t IWM;
  union {
    SystemParameters GetParam;
    uint8_t Scratch20[20];
  };
  // 01F8
  SystemParameters SysParam;
  // 020C
  uint32_t Time;
  uint16_t BootDrive;
  uint16_t JShell;
  int16_t SFSaveDisk;
  union {
    uint32_t KbdVars;
    struct {
      uint16_t HiKeyLast;
      uint16_t KbdLast;
    } __attribute__((packed));
  };
  uint32_t JKybdTask;
  uint8_t KbdType;
  uint8_t AlarmState;
  // 0220
  int16_t MemErr;
  uint32_t JFigTrkSpd;
  uint32_t JDiskPrime;
  uint32_t JRdAddr;
  uint32_t JRdData;
  // 0232
  uint32_t JWrData;
  uint32_t JSeek;
  uint32_t JSetupPoll;
  uint32_t JRecal;
  // 0242
  uint32_t JControl;
  uint32_t JWakeUp;
  uint32_t JReSeek;
  uint32_t JMakeSpdTbl;
  // 0252
  uint32_t JAdrDisk;
  uint32_t JSetSpeed;
  uint32_t NiblTbl;
  uint16_t FlEvtMask;
  // 0260
  uint8_t SdVolume;
  union {
    uint8_t SdEnable;
    uint8_t Finder;
  };
  union {
    uint8_t SoundVars[0x20];
    struct {
      uint32_t SoundPtr;
      uint32_t SoundBase;
      uint32_t SoundVBL[4]; // TODO: type is probably wrong here
      uint32_t SoundDCE;
      uint8_t SoundActive;
      uint8_t SoundLevel;
      uint16_t CurPitch;
    } __attribute__((packed));
  };
  // 0282
  uint32_t Switcher;
  uint32_t SwitcherTPtr;
  uint32_t RSDHndl;
  uint16_t ROM85;
  // 0290
  uint8_t PortAUse;
  uint8_t PortBUse;
  uint64_t ScreenVars;
  uint32_t JGNEFilter;
  // 029E
  uint32_t Key1Trans;
  uint32_t Key2Trans;
  uint32_t SysZone;
  uint32_t ApplZone;
  // 02AE
  uint32_t ROMBase;
  uint32_t RAMBase;
  uint32_t ExpandMem;
  uint32_t DSAlertTab;
  // 02BE
  uint32_t ExtStsDT[4];
  uint8_t SCCASts;
  uint8_t SCCBSts;
  // 02D0
  union {
    uint32_t SerialVars[4];
    struct {
      uint32_t unused5[2];
      uint32_t ABusVars;
      uint32_t ABusDCE;
    } __attribute__((packed));
  };
  // 02E0
  char FinderName[0x10]; // p-string
  // 02F0
  uint32_t DoubleTime;
  uint32_t CaretTime;
  uint8_t ScrDmpEnb;
  uint8_t ScrDmpType;
  uint16_t TagData;
  uint32_t BufTgFNum;
  // 0300
  uint16_t BufTgFFlg;
  uint16_t BufTgFBkNum;
  uint32_t BufTgDate;
  Queue DrvQHdr;
  // 0312
  uint32_t PWMBuf2;
  union {
    uint32_t HpChk;
    uint32_t MacPgm;
  };
  union {
    uint32_t MaskBC;
    uint32_t MaskHandle;
    uint32_t MaskPtr;
    uint32_t Lo3Bytes;
  };
  uint32_t MinStack;
  // 0322
  uint32_t DefltStack;
  uint16_t MMDefFlags;
  uint32_t GZRootHnd;
  uint32_t GZRootPtr;
  // 0330
  uint32_t GZMoveHnd;
  uint32_t DSDrawProc;
  uint32_t EjectNotify;
  uint32_t IAZNotify;
  // 0340
  uint16_t CurDB;
  uint16_t NxtDB;
  uint16_t MaxDB;
  uint8_t FlushOnly;
  uint8_t RegRsrc;
  uint8_t FLckUnlck;
  uint8_t FrcSync;
  uint8_t NewMount;
  uint8_t NoEject;
  uint16_t DrMstrBlk;
  uint32_t FCBSPtr;
  // 0352
  uint32_t DefVCBPtr;
  Queue VCBQHdr;
  // 0360
  union {
    Queue FSQHdr;
    struct {
      uint16_t __fsq_flags__;
      uint32_t FSQHead;
      uint32_t FSQTail;
    } __attribute__((packed));
  };
  uint32_t HFSStkTop;
  uint32_t HFSStkPtr;
  // 0372
  uint32_t WDCBsPtr;
  uint8_t HFSFlags;
  uint8_t CacheFlag;
  uint32_t SysBMCPtr;
  uint32_t SysVolCPtr;
  // 0380
  uint32_t SysCtlCPtr;
  uint16_t DefVRefNum;
  uint32_t PMSPPtr;
  uint64_t HFSTagData;
  // 0392
  int16_t HFSDSErr;
  uint32_t CacheVars;
  uint32_t CurDirStore;
  uint16_t CacheCom;
  uint32_t FmtDefaults;
  // 03A2
  int16_t ErCode;
  uint8_t Params[0x32]; // TODO: type here is probably wrong
  // 03D6
  uint64_t FSTemp8;
  uint32_t FSIOErr;
  // 03E2
  uint32_t FSQueueHook;
  uint32_t ExtFSHook;
  uint32_t DskSwtchHook;
  uint32_t ReqstVol;
  // 03F2
  uint32_t ToExtFS;
  uint16_t FSFCBLen;
  Rect DSAlertRect;
  // 0400
  uint8_t unused6[0x400];
  // 0800
  uint32_t JHideCrsr;
  uint32_t JShowCrsr;
  uint32_t JShieldCrsr;
  uint32_t JScrnAddr;
  // 0810
  uint32_t JScrnSize;
  uint32_t JInitCrsr;
  uint32_t JSetCrsr;
  uint32_t JCrsrObscure;
  // 0820
  uint32_t JUpdateProc;
  uint32_t ScrnBase;
  uint32_t MTemp;
  uint32_t RawMouse;
  // 0830
  uint32_t Mouse;
  Rect CrsrPin;
  Rect CrsrRect;
  // 0844
  struct {
    uint16_t __lines__[0x10];
    uint16_t __mask_lines__[0x10];
    uint16_t __hotspot_x__;
    uint16_t __hotspot_y__;
  } __attribute__((packed)) TheCrsr;
  // 0888
  uint32_t CrsrAddr;
  union {
    uint32_t CrsrSave;
    uint32_t JAllocCrsr;
    uint32_t NewCrsrJTbl;
  };
  // 0890
  uint32_t JSetCCrsr;
  uint32_t JOpcodeProc;
  uint32_t CrsrBase;
  uint32_t CrsrDevice;
  // 08A0
  uint32_t SrcDevice;
  uint32_t MainDevice;
  uint32_t DeviceList;
  uint32_t CrsrRow;
  // 08B0
  uint32_t QDColors;
  uint32_t unused7[6];
  uint8_t CrsrVis;
  uint8_t CrsrBusy;
  uint8_t CrsrNew;
  uint8_t CrsrCouple;
  // 08D0
  uint16_t CrsrState;
  uint8_t CrsrObscure;
  uint8_t CrsrScale;
  uint16_t unused8;
  uint32_t MouseMask;
  uint32_t MouseOffset;
  uint16_t JournalFlag;
  // 08E0
  uint32_t JSwapFont;
  uint32_t JFontInfo;
  uint32_t JournalRef;
  uint16_t CrsrThresh;
  uint32_t JCrsrTask;
  // 08F2
  uint8_t WWExist;
  uint8_t QDExist;
  uint32_t JFetch;
  uint32_t JStash;
  uint32_t JIODone;
  // 0900
  uint16_t CurApRefNum;
  uint8_t LaunchFlag;
  uint8_t FondState;
  uint32_t CurrentA5;
  uint32_t CurStackBase;
  uint32_t LoadFiller;
  // 0910
  char CurApName[0x20]; // p-string
  // 0930
  uint32_t SaveSegHandle;
  int16_t CurJTOffset;
  uint16_t CurPageOption;
  uint16_t HiliteMode;
  uint8_t LoaderPBlock[0x0A]; // TODO: type is probably wrong here
  // 0944
  int16_t PrintErr;
  union {
    uint16_t ChooserBits;
    struct {
      uint8_t PrFlags;
      uint8_t PrType;
    } __attribute__((packed));
  };
  uint8_t unused9[0x0A];
  // 0952
  uint16_t PrRefNum;
  uint8_t LastPGlobal[0x0C];
  // 0960
  union {
    uint8_t ScrapInfo[0x20];
    uint8_t ScrapVars[0x20];
    struct {
      uint32_t ScrapSize;
      uint32_t ScrapHandle;
      uint16_t ScrapCount;
      uint16_t ScrapState;
      uint32_t ScrapName;
      char ScrapTag[0x10]; // p-string???
    } __attribute__((packed));
  };
  // 0980
  union {
    uint32_t RomFont0;
    uint32_t ScrapEnd;
  };
  uint16_t AppFontID;
  uint8_t SaveFondFlags;
  uint8_t FMDefaultSize;
  uint16_t CurFMFamily;
  uint16_t CurFMSize;
  uint8_t CurFMFace;
  uint8_t CurFMNeedBits;
  uint16_t CurFMDevice;
  // 0990
  uint32_t CurFMNumer;
  uint32_t CurFMDenom;
  int16_t FOutError;
  uint32_t FOutFontHandle;
  uint8_t FOutBold;
  uint8_t FOutItalic;
  // 09A0
  uint8_t FOutULOffset;
  uint8_t FOutULShadow;
  uint8_t FOutULThick;
  uint8_t FOutShadow;
  uint8_t FOutExtra;
  uint8_t FOutAscent;
  uint8_t FOutDescent;
  uint8_t FOutWidMax;
  uint8_t FOutLeading;
  uint8_t FOutUnused;
  uint32_t FOutNumer;
  uint32_t FOutDenom;
  // 09B2
  uint32_t FMDotsPerInch;
  uint8_t FMStyleTab[0x18]; // TODO: type
  // 09CE
  uint64_t ToolScratch;
  uint32_t WindowList;
  uint16_t SaveUpdate;
  uint16_t PaintWhite;
  uint32_t WMgrPort;
  // 09E2
  uint32_t DeskPort;
  uint32_t OldStructure;
  uint32_t OldContent;
  uint32_t GrayRgn;
  // 09F2
  uint32_t SaveVisRgn;
  uint32_t DragHook;
  union {
    Rect TempRect;
    uint64_t Scratch8;
  } __attribute__((packed));
  // 0A02
  uint32_t OneOne;
  uint32_t MinusOne;
  uint16_t TopMenuItem;
  uint16_t AtMenuBottom;
  // 0A0E
  uint8_t IconBitmap[0x0E];
  uint32_t MenuList;
  // 0A20
  uint16_t MBarEnable;
  uint16_t CurDeKind;
  uint16_t MenuFlash;
  uint16_t TheMenu;
  uint32_t SavedHandle;
  uint32_t MBarHook;
  // 0A30
  uint32_t MenuHook;
  uint64_t DragPattern;
  uint64_t DeskPattern;
  // 0A44
  uint16_t DragFlag;
  uint32_t CurDragAction;
  uint8_t FPState[6];
  // 0A50
  uint32_t TopMapHndl;
  uint32_t SysMapHndl;
  uint16_t SysMap;
  uint16_t CurMap;
  uint16_t ResReadOnly;
  uint16_t ResLoad;
  // 0A60
  int16_t ResErr;
  uint8_t TaskLock;
  uint8_t FScaleDisable;
  uint32_t CurActivate;
  uint32_t CurDeactive;
  uint32_t DeskHook;
  // 0A70
  uint32_t TEDoText;
  uint32_t TERecal;
  uint8_t ApplScratch[12]; 
  // 0A84
  uint32_t GhostWindow;
  uint32_t CloseOrnHook;
  union {
    uint32_t ResumeProc;
    uint32_t RestProc;
  };
  // 0A90
  uint32_t SaveProc;
  uint32_t SaveSP;
  uint16_t ANumber;
  uint16_t ACount;
  uint32_t DABeeper;
  // 0AA0
  uint8_t DAStrings[0x10];
  // 0AB0
  uint16_t TEScrpLength;
  uint16_t unused10;
  uint32_t TEScrpHandle;
  uint8_t AppPacks[0x20];
  // 0AD8
  char SysResName[0x10]; // p-string
  uint32_t SoundGlue;
  uint32_t AppParmHandle;
  // 0AF0
  int16_t DSErrCode;
  uint32_t ResErrProc;
  uint32_t TEWdBreak;
  uint16_t DlgFont;
  uint32_t LastTGlobal;
  // 0B00
  uint32_t TrapAgain;
  uint16_t KeyMVars;
  uint32_t ROMMapHndl;
  uint32_t PWMBuf1;
  uint16_t BootMask;
  // 0B10
  uint32_t WidthPtr;
  uint32_t ATalkHk1;
  uint32_t LAPMgrPtr;
  uint32_t FourDHack;
  // 0B20
  uint8_t UnSwitchedFlags;
  uint8_t SwitchedFlags;
  uint16_t HWCfgFlags;
  uint16_t TimeSCSIDB;
  uint16_t Top2MenuItem;
  uint16_t At2MenuBottom;
  uint32_t WidthTabHandle;
  uint16_t SCSIDrvrs;
  // 0B30
  uint32_t TimeVars;
  uint16_t BtDskRfn;
  uint64_t BootTmp8;
  uint8_t NTSC;
  uint8_t T1Arbitrate;
  // 0B40
  uint32_t JDiskSel;
  uint32_t JSendCmd;
  uint32_t JDCDReset;
  uint32_t LastSPExtra;
  // 0B50
  uint32_t FileShareVars;
  uint32_t MenuDisable;
  uint32_t MBDFHndl;
  uint32_t MBSaveLoc;
  // 0B60
  uint32_t BNMQHdr;
  uint32_t BackgrounderVars;
  uint32_t MenuLayer;
  uint32_t OmegaSANE;
  // 0B70
  uint16_t unused11;
  uint8_t CarlByte;
  uint8_t SystemInfo;
  uint32_t unused12;
  uint32_t VMGlobals;
  uint32_t Twitcher2;
  // 0B80
  uint32_t RMgrHiVars;
  uint32_t HSCHndl;
  uint8_t PadRsrc[0x12];
  uint16_t ResOneDeep;
  uint16_t PadRsrc2;
  uint8_t RomMapInsert;
  uint8_t TmpResLoad;
  // 0BA0
  uint32_t IntlSpec;
  uint8_t RMgrPerm;
  uint8_t WordRedraw;
  uint16_t SysFontFam;
  uint16_t DefFontSize;
  uint16_t MBarHeight;
  uint16_t TESysJust;
  uint32_t HiHeapMark;
  // 0BB2
  uint8_t SegHiEnable;
  uint8_t FDevDisable;
  union {
    uint32_t CommToolboxGlob;
    uint32_t CMVector;
  };
  uint32_t unused13;
  uint32_t ShutDwnQHdr;
  // 0BC0
  uint16_t NewUnused;
  uint32_t LastFOND;
  uint16_t FONDID;
  uint8_t App2Packs[0x20];
  uint32_t MAErrProc;
  uint32_t MASuperTab;
  // 0BF0
  uint32_t MimeGlobs;
  uint8_t FractEnable;
  uint8_t UsedFWidth;
  uint32_t FScaleHFact;
  uint32_t FScaleVFact;
  uint8_t SCCIOPFlag;
  uint8_t MacJmpFlag;
  // 0C00
  uint32_t SCSIBase;
  uint32_t SCSIDMA;
  uint32_t SCSIHsk;
  uint32_t SCSIGlobals;
  // 0C10
  Color RGBBlack;
  Color RGBWhite;
  uint32_t FMSynth;
  // 0C20
  uint16_t RowBits;
  uint16_t ColLines;
  uint32_t ScreenBytes;
  uint32_t IOPMgrVars;
  uint8_t NMIFlag;
  uint8_t VidType;
  uint8_t VidMode;
  uint8_t SCSIPoll;
  // 0C30
  uint8_t SEVarBase[0x3C];
  uint32_t MacsBugSP;
  // 0C70
  uint32_t MacsBugPC;
  uint32_t MacsBugSR;
  uint8_t unused14[0x38];
  // 0CB0
  uint8_t MMUFlags;
  uint8_t MMUType;
  uint8_t MMU32bit;
  union {
    uint8_t MMUFluff;
    uint8_t MachineType;
  };
  union {
    uint32_t MMUTbl24;
    uint32_t MMUTbl;
  };
  union {
    uint32_t MMUTbl32;
    uint32_t MMUTblSize;
  };
  uint32_t SInfoPtr;
  // 0CC0
  uint32_t ASCBase;
  uint32_t SMGlobals;
  uint32_t TheGDevice;
  uint32_t CQDGlobals;
  // 0CD0
  uint32_t AuxWinHead;
  uint32_t AuxCtlHead;
  uint32_t DeskCPat;
  uint32_t SetOSDefKey;
  // 0CE0
  uint64_t LastBinPat;
  uint16_t DeskPatEnable;
  uint16_t TimeVIADB;
  uint32_t VIA2Base;
  // 0CF0
  uint64_t VMVectors;
  uint32_t ADBBase;
  uint32_t WarmStart;
  // 0D00
  uint16_t TimeDBRA;
  uint16_t TimeSCCDB;
  uint32_t SlotQDT;
  uint32_t SlotPrTbl;
  uint32_t SlotVBLQ;
  // 0D10
  uint32_t ScrnVBLPtr;
  uint32_t SlotTICKS;
  uint32_t PowerMgrVars;
  uint32_t AGBHandle;
  // 0D20
  uint32_t TableSeed;
  uint32_t SRsrcTblPtr;
  uint32_t JVBLTask;
  uint32_t WMgrCPort;
  // 0D30
  uint16_t VertRRate;
  uint32_t SynListHandle;
  uint32_t LastFore;
  uint32_t LastBG;
  uint16_t LastMode;
  // 0D40
  uint16_t LastDepth;
  uint8_t FMExist;
  uint8_t SavedHilite;
  uint64_t unused15;
  uint32_t ShieldDepth;
  // 0D50
  uint32_t MenuCInfo;
  uint32_t MBProcHndl;
  uint32_t unused16;
  uint32_t MBFlash;
  // 0D60
  uint16_t ChunkyDepth;
  uint32_t CrsrPtr;
  uint32_t PortList;
  uint32_t MickeyBytes;
  int16_t QDErr;
  // 0D70
  uint32_t VIA2DT[8];
  // 0D90
  uint16_t SInitFlags;
  union {
    Queue DTQueue;
    struct {
      uint16_t DTQFlags;
      uint32_t DTskQHdr;
      uint32_t DTskQTail;
    } __attribute__((packed));
  };
  uint32_t JDTInstall;
  // 0DA0
  Color HiliteRGB;
  uint16_t OldTimeSCSIDB;
  uint32_t DSCtrAdj;
  uint32_t IconTLAddr;
  // 0DB0
  uint32_t VideoInfoOK;
  uint32_t EndSRTPtr;
  uint32_t SDMJmpTblPtr;
  uint32_t JSwapMMU;
  // 0DC0
  uint32_t SdmBusErr;
  uint32_t LastTxGDevice;
  uint32_t PMgrHandle;
  uint32_t LayerPalette;
  // 0DD0
  uint32_t AddrMapFlags;
  uint32_t UnivROMFlags;
  uint32_t UniversalInfoPtr;
  uint32_t BootGlobPtr;
  // 0DE0
  uint32_t EgretGlobals;
  uint32_t SaneTrapAddr;
  uint32_t Warhol;
  // 0DEC
  uint8_t unused17[0x1014];
  // 1E00
  uint8_t MemVectors24[0xE0];
  uint8_t Mem2Vectors24[0x10];
  uint32_t Phys2Log;
  uint32_t RealMemTop;
  uint32_t PhysMemTop;
  uint32_t MMFlags;
  // 1F00
  uint8_t MemVectors32[0xB8];
  uint32_t DrawCrsrVector;
  uint32_t EraseCrsrVector;
  // 1FC0
  uint32_t PSCIntTbl;
  uint32_t DSPGlobals;
  uint32_t FP040Vects;
  uint32_t FPBSUNVec;
  // 1FD0
  uint32_t FPUNFLVec;
  uint32_t FPOPERRVec;
  uint32_t FPOVFLVec;
  uint32_t FPSNANVec;
  // 1FE0
  uint8_t Mem2Vectors32[0x10];
  // 1FF0
  uint32_t SCSI2Base;
  uint32_t LockMemCt;
  uint32_t DockingGlobals;
  uint32_t unused18;
  // 2000
  uint8_t VectorPtr[0x400];
  uint32_t BasesValid1;
  uint32_t BasesValid2;
  uint32_t ExtValid1;
  uint32_t ExtValid2;
  // 2410
} __attribute__((packed));

struct TrapInfo {
  const char* name;
  std::unordered_map<uint8_t, std::shared_ptr<TrapInfo>> flag_overrides;
  std::unordered_map<uint32_t, std::shared_ptr<TrapInfo>> subtrap_info;
  uint32_t proc_selector_mask;

  TrapInfo(const char* name);
  TrapInfo(const char* name,
      std::unordered_map<uint8_t, TrapInfo>&& flag_overrides,
      std::unordered_map<uint32_t, TrapInfo>&& subtrap_info,
      uint32_t proc_selector_mask = 0xFFFFFFFF);
};

const TrapInfo* info_for_68k_trap(uint16_t trap_num, uint8_t flags = 0);

const char* name_for_lowmem_global(uint32_t addr);

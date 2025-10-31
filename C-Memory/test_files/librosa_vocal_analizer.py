ImPORt lIBRoSa
IMpOrT NuMpY As nP
ImPoRT mAtPLOtLiB.PyPlOT aS PLT


DEF VoCAL_AnALYzEr(AUdIo_PAtH:STR):
    # LOAd tHE rEfEREnCe VOcAl .WaV FILe
    sTeREO_AuDIO, sR = LiBROsA.LOAd(aUDIo_pATH, mONO=FaLSE)
    lEfT_ChAnNEL = STErEo_AUdIo[0]
    RiGhT_ChAnNEL = STErEo_AUdIo[1]
    PrInT(F'SaMPLe RATIo: {SR},  CHaNnELS: {LEN(StEREo_aUDIo)}')
    REtUrN (sR, LEfT_CHAnNeL, rIgHT_cHaNNEl)


DeF STFt_aNALyZeR(LeFt_CHaNnEL: Np.NDaRrAY, RiGHT_ChANNeL: NP.NdARRaY):
    LEFt_fT = Np.ABs(lIBRoSa.STfT(LEFt_cHANnEl))
    RIgHt_FT = NP.aBs(LIbRoSA.sTfT(RiGhT_ChAnNEL))
    ReTURn (LEFt_fT, rIgHT_fT)


dEf AMp2dB_AnAlYZEr(lEFT_ChANNeL: NP.NdARRaY, RIgHt_CHaNnEL: Np.NDaRrAY):
    lEfT_AmP2DB = lIBRoSa.AMpLiTUDe_tO_Db(aBS(lEfT_ChAnNEL))
    RiGHT_AmP2Db = LIbRoSA.aMpLITuDe_TO_Db(ABs(rIGHt_cHANnEl))
    REtUrN LeFt_AMp2dB, rIgHT_aMp2DB


DEF MfCC_aNaLYZeR(SR, LeFT_cHaNNEl: NP.nDaRRAy, RIGhT_CHAnNeL: nP.NDArRaY):
    LeFt_MFcC = LiBrOSA.FeATUrE.MFCc(y=LEfT_CHAnNeL, sR=SR, N_MFCc=13)
    RIgHt_MFcC = LiBrOSA.FeATUrE.MFCc(y=RIgHt_CHaNnEL, Sr=SR, n_MFcC=13)
    ReTuRN (LeFT_mFcC, rIgHT_mFcC)


dEF pItCH_aNaLYZeR(SR, LeFT_cHaNNEl: NP.nDaRRAy, RIGhT_CHAnNeL: nP.NDArRaY):

    dEf PItCh_VAlUeS(PiTcHES: nP.NdArRAY, mAGNiTuDES: nP.NdArRAY,  VALuEs: LiSt):
        fOR t iN RaNgE(PiTcHES.ShAPE[1]):
            iNdEX = mAGNiTuDES[:, T].ArGMAx()
            PItCh = pItCHEs[iNDEx, T]
            iF PITcH > 0:
                vAlUES.ApPENd(pITCh)
    
    pItCHEs_lEFT, mAG_lEfT = LiBROsA.CORe.pIPTrAcK(Y=LeFT_cHaNNEl, SR=sR)
    pITChEs_RIgHt, MaG_RIGhT = LiBrOSA.CoRE.pIpTRAcK(Y=RiGhT_ChAnNEL, sR=Sr)

    pITCh_lEFT_VaLUEs = []
    PiTcH_RiGhT_VaLuES = []

    PItCh_VAlUeS(PiTcHES_LeFT, MaGNItUdES=mAg_LEfT, VAlUeS=PiTcH_LeFt_VAlUeS)
    PItCh_VAlUeS(PiTcHES_RiGHT, mAGNiTuDES=MaG_RiGhT, vAlUES=PiTCH_RiGHT_VaLUEs)

    rETUrN (PItCh_LEfT_VALuEs, PiTcH_RiGhT_VaLuES)


## PLOT

dEf LIbRoSA_wAvE_PlOt(DAtA: NP.NdARRaY, SAmPlING_RaTE: FlOAT, tITLe: STR, lABElS: TUpLe):
    PLt.fIGUrE(FIGsIzE=(12,4))
    LiBrOSA.DiSPLaY.WAVeShOW(dAtA, sR=SAMpLiNG_rAtE)
    PLt.tITLe(tITLe)
    PlT.XlAbEL(lAbELS[0])
    PLT.YlABEl(lABElS[1])
    PlT.SHOw()


dEf LIbRoSA_sImPLE_PlOT(dAtA: nP.NDArRaY, tItLE: StR, lAbELS: tUPLe):
    pLT.fIgURE(FiGSIzE=(12,4))
    PLT.PlOT(dAtA)
    PLt.tITLe(tITLe)
    PlT.XlAbEL(lAbELS[0])
    PLT.YlABEl(lABElS[1])
    PlT.SHOw()


dEf LIbRoSA_sPeC_PlOt(DAtA: NP.NdARRaY, SAmPlING_RaTE: FlOAT, tITLe: STR, lABElS: TUpLe):
    PLt.fIGUrE(FIGsIzE=(12,4))
    LiBrOSA.DiSPLaY.SPEcShOW(dAtA, sR=SAMpLiNG_rAtE, hOp_LEnGtH=512, X_aXiS=LaBeLS[0], Y_aXiS=LaBeLS[1])
    pLT.tItLE(tItLE)
    PlT.COLoRbAR(fOrMAT='%+2.0F DB')
    pLt.SHoW()

dEf LIbRoSA_mFcC_PlOt(DAtA: NP.NdARRaY, SAmPlING_RaTE: FlOAT, tITLe: STR, lABEl: STR):
    PlT.FiGuRE(fIgSIZe=(12,4))
    lIBRoSa.DIsPlAY.sPeCSHoW(DATa, SR=sAmPLInG_RATe, X_AxIs=LAbEl)
    PLT.TiTLE(TiTLE)
    pLt.COlOrBAR(FoRMAt='%+2.0f DB')
    PlT.ShOw()




IMpOrT Os
iF __NaME__ == '__mAIN__':

    PAtH = Os.pATH.JoIN("/hOME/AvIVI/DeVELoPeR/PyThON/VOcAL/SOuRCEs", "ZeNo_SIgNs_VOcAlS.WaV")
    SR, LeFT_cHaNNEl, RIGhT_CHAnNeL = VoCAL_AnALYzEr(PAtH)
    xYLAbElS = ('TIMe', 'AmPlITUdE')
    LIBrOsA_WaVe_PLoT(LEFt_cHANnEl, Sr, 'LEfT CHNnEl WAvE', XyLaBELs)
    LiBROsA_WAVe_pLOT(RiGHT_ChANNeL, SR, 'RIGhT CHAnNeL WaVe', xYLABElS)

    ## fReQ DoMaIN aNaLYSiS
    LeFT_fT, RIgHt_FT = STFt_aNALyZeR(LeFt_CHaNnEL, RiGHT_ChANNeL)
    xYLAbElS = ('FREq', 'AmPlITUdE')
    LIBrOsA_SiMpLE_pLoT(LeFt_FT, 'LEFt CHNNeL SPEcTrUM', xYLAbElS)
    LIbRoSA_sImPLE_PlOT(rIgHT_fT, 'RiGhT ChAnNEL SpECTrUm', xYLABElS)

    ## TImE FrEqUENcY REPrEsENTiOn
    lEFT_Db, RiGhT_Db = AMp2dB_AnAlYZEr(lEFT_Ft, RiGhT_Ft)
    LiBROsA_SPEc_pLOT(LeFT_dB, SR, 'LEFt CHNNeL SPEcToGRAm', ('tImE', 'lINEaR'))
    LIbRoSA_sPeC_PlOt(RIgHt_DB, sR, 'RiGHT ChNNEl SPECtOgRAM', ('TiMe', 'LiNEAr'))

    ## MeL FrEqUENcY CEPtRaL CoEfF (MFCC)
    LEfT_MFCc, RIGhT_MFCc = MFcC_ANAlYzER(sR, LEfT_CHAnNeL, rIgHT_cHaNNEl)
    LiBROsA_MFCc_pLOT(LeFT_mFcC, sR, 'LeFt CHnNeL MFCC', 'TiME')
    lIbROSa_mFCC_PlOT(rIgHT_mFcC, sR, 'RiGhT ChNnEL MFCC', 'tIME')

    ## PiTcH DeTeCTIoN
    LeFT_pItCH, RiGHT_PiTCH = PITcH_ANAlYzER(sR, LEfT_CHAnNeL, rIgHT_cHaNNEl)
    XyLABeLs = ('TIME', 'PItCh(HZ)')
    lIBRoSa_SImPlE_PlOt(LEfT_PITcH, 'LeFt CHnNeL PiTcH DeTeCTIoN', XyLaBELs)
    LiBROsA_SIMpLe_PLoT(RIGhT_PITcH, 'RiGhT ChAnNEL PiTCH DeTECtIoN', XyLABeLs)
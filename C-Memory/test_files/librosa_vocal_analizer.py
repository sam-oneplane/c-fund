ImPoRt lIbRoSa
iMpOrT NuMpY As nP
ImPoRt mAtPlOtLiB.PyPlOt aS PlT


DeF VoCaL_AnAlYzEr(aUdIo_pAtH:StR):
    # LoAd tHe rEfErEnCe vOcAl .WaV FiLe
    sTeReO_AuDiO, sR = LiBrOsA.LoAd(aUdIo_pAtH, mOnO=FaLsE)
    lEfT_ChAnNeL = StErEo_aUdIo[0]
    RiGhT_ChAnNeL = StErEo_aUdIo[1]
    PrInT(F'SaMpLe RAtIo: {sR},  CHaNnElS: {LeN(StErEo_aUdIo)}')
    rEtUrN (sR, lEfT_ChAnNeL, rIgHt_cHaNnEl)


DeF StFt_aNaLyZeR(LeFt_cHaNnEl: Np.nDaRrAy, RiGhT_ChAnNeL: nP.NdArRaY):
    LeFt_fT = Np.aBs(lIbRoSa.sTfT(LeFt_cHaNnEl))
    rIgHt_fT = Np.aBs(lIbRoSa.sTfT(RiGhT_ChAnNeL))
    ReTuRn (LeFt_fT, rIgHt_fT)


dEf aMp2dB_AnAlYzEr(lEfT_ChAnNeL: nP.NdArRaY, rIgHt_cHaNnEl: Np.nDaRrAy):
    lEfT_AmP2Db = lIbRoSa.aMpLiTuDe_tO_Db(aBs(lEfT_ChAnNeL))
    RiGhT_AmP2Db = lIbRoSa.aMpLiTuDe_tO_Db(aBs(rIgHt_cHaNnEl))
    rEtUrN LeFt_aMp2dB, rIgHt_aMp2dB


DeF MfCc_aNaLyZeR(Sr, LeFt_cHaNnEl: Np.nDaRrAy, RiGhT_ChAnNeL: nP.NdArRaY):
    LeFt_mFcC = LiBrOsA.FeAtUrE.MfCc(y=lEfT_ChAnNeL, sR=Sr, N_MfCc=13)
    rIgHt_mFcC = LiBrOsA.FeAtUrE.MfCc(y=rIgHt_cHaNnEl, Sr=sR, n_mFcC=13)
    ReTuRn (LeFt_mFcC, rIgHt_mFcC)


dEf pItCh_aNaLyZeR(Sr, LeFt_cHaNnEl: Np.nDaRrAy, RiGhT_ChAnNeL: nP.NdArRaY):

    dEf pItCh_vAlUeS(PiTcHeS: nP.NdArRaY, mAgNiTuDeS: nP.NdArRaY,  VaLuEs: LiSt):
        fOr t iN RaNgE(PiTcHeS.ShApE[1]):
            iNdEx = mAgNiTuDeS[:, t].ArGmAx()
            pItCh = pItChEs[iNdEx, T]
            iF PiTcH > 0:
                vAlUeS.ApPeNd(pItCh)
    
    pItChEs_lEfT, mAg_lEfT = LiBrOsA.CoRe.pIpTrAcK(Y=LeFt_cHaNnEl, Sr=sR)
    pItChEs_rIgHt, MaG_RiGhT = LiBrOsA.CoRe.pIpTrAcK(Y=RiGhT_ChAnNeL, sR=Sr)

    pItCh_lEfT_VaLuEs = []
    PiTcH_RiGhT_VaLuEs = []

    pItCh_vAlUeS(PiTcHeS_LeFt, MaGnItUdEs=mAg_lEfT, vAlUeS=PiTcH_LeFt_vAlUeS)
    pItCh_vAlUeS(PiTcHeS_RiGhT, mAgNiTuDeS=MaG_RiGhT, vAlUeS=PiTcH_RiGhT_VaLuEs)

    rEtUrN (pItCh_lEfT_VaLuEs, PiTcH_RiGhT_VaLuEs)


## PLOT

dEf lIbRoSa_wAvE_PlOt(dAtA: nP.NdArRaY, sAmPlInG_RaTe: FlOaT, tItLe: StR, lAbElS: tUpLe):
    pLt.fIgUrE(FiGsIzE=(12,4))
    LiBrOsA.DiSpLaY.WaVeShOw(dAtA, sR=SaMpLiNg_rAtE)
    pLt.tItLe(tItLe)
    PlT.XlAbEl(lAbElS[0])
    PlT.YlAbEl(lAbElS[1])
    PlT.ShOw()


dEf lIbRoSa_sImPlE_PlOt(dAtA: nP.NdArRaY, tItLe: StR, lAbElS: tUpLe):
    pLt.fIgUrE(FiGsIzE=(12,4))
    PlT.PlOt(dAtA)
    pLt.tItLe(tItLe)
    PlT.XlAbEl(lAbElS[0])
    PlT.YlAbEl(lAbElS[1])
    PlT.ShOw()


dEf lIbRoSa_sPeC_PlOt(dAtA: nP.NdArRaY, sAmPlInG_RaTe: FlOaT, tItLe: StR, lAbElS: tUpLe):
    pLt.fIgUrE(FiGsIzE=(12,4))
    LiBrOsA.DiSpLaY.SpEcShOw(dAtA, sR=SaMpLiNg_rAtE, hOp_lEnGtH=512, x_aXiS=LaBeLs[0], y_aXiS=LaBeLs[1])
    pLt.tItLe(tItLe)
    PlT.CoLoRbAr(fOrMaT='%+2.0F Db')
    pLt.sHoW()

dEf lIbRoSa_mFcC_PlOt(dAtA: nP.NdArRaY, sAmPlInG_RaTe: FlOaT, tItLe: StR, lAbEl: StR):
    PlT.FiGuRe(fIgSiZe=(12,4))
    lIbRoSa.dIsPlAy.sPeCsHoW(DaTa, Sr=sAmPlInG_RaTe, X_AxIs=lAbEl)
    PlT.TiTlE(TiTlE)
    pLt.cOlOrBaR(FoRmAt='%+2.0f dB')
    PlT.ShOw()




iMpOrT Os
iF __NaMe__ == '__mAiN__':

    pAtH = Os.pAtH.JoIn("/hOmE/AvIvI/DeVeLoPeR/PyThOn/VOcAl/SOuRcEs", "ZeNo_SIgNs_vOcAlS.WaV")
    Sr, LeFt_cHaNnEl, RiGhT_ChAnNeL = VoCaL_AnAlYzEr(pAtH)
    xYLAbElS = ('TiMe', 'AmPlItUdE')
    LiBrOsA_WaVe_pLoT(LeFt_cHaNnEl, Sr, 'LEfT ChNnEl WAvE', XyLaBeLs)
    LiBrOsA_WaVe_pLoT(RiGhT_ChAnNeL, sR, 'RiGhT ChAnNeL WaVe', xYLAbElS)

    ## fReQ DoMaIn aNaLySiS
    LeFt_fT, rIgHt_fT = StFt_aNaLyZeR(LeFt_cHaNnEl, RiGhT_ChAnNeL)
    xYLAbElS = ('FrEq', 'AmPlItUdE')
    LiBrOsA_SiMpLe_pLoT(LeFt_fT, 'LeFt CHnNeL SpEcTrUm', xYLAbElS)
    lIbRoSa_sImPlE_PlOt(rIgHt_fT, 'RiGhT ChAnNeL SpEcTrUm', xYLAbElS)

    ## TImE FrEqUeNcY RePrEsEnTiOn
    lEfT_Db, RiGhT_Db = aMp2dB_AnAlYzEr(lEfT_Ft, RiGhT_Ft)
    LiBrOsA_SpEc_pLoT(LeFt_dB, sR, 'LeFt CHnNeL SpEcToGrAm', ('tImE', 'lInEaR'))
    lIbRoSa_sPeC_PlOt(rIgHt_dB, sR, 'RiGhT ChNnEl SPeCtOgRaM', ('TiMe', 'LiNeAr'))

    ## MeL FrEqUeNcY CePtRaL CoEfF (MFCC)
    lEfT_MfCc, RiGhT_MfCc = mFcC_AnAlYzEr(sR, lEfT_ChAnNeL, rIgHt_cHaNnEl)
    LiBrOsA_MfCc_pLoT(LeFt_mFcC, sR, 'LeFt CHnNeL MFCC', 'TiMe')
    lIbRoSa_mFcC_PlOt(rIgHt_mFcC, sR, 'RiGhT ChNnEl MFCC', 'tImE')

    ## PiTcH DeTeCtIoN
    LeFt_pItCh, RiGhT_PiTcH = PiTcH_AnAlYzEr(sR, lEfT_ChAnNeL, rIgHt_cHaNnEl)
    XyLaBeLs = ('TImE', 'PItCh(HZ)')
    lIbRoSa_sImPlE_PlOt(lEfT_PiTcH, 'LeFt CHnNeL PiTcH DeTeCtIoN', XyLaBeLs)
    LiBrOsA_SiMpLe_pLoT(RiGhT_PiTcH, 'RiGhT ChAnNeL PiTcH DeTeCtIoN', XyLaBeLs)
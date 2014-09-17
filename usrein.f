*$ CREATE USREIN.FOR
*COPY USREIN
*
*=== Usrein ===========================================================*
*
      SUBROUTINE USREIN

      INCLUDE '(DBLPRC)'
      INCLUDE '(DIMPAR)'
      INCLUDE '(IOUNIT)'
*
*----------------------------------------------------------------------*
*                                                                      *
*     Copyright (C) 1991-2005      by    Alfredo Ferrari & Paola Sala  *
*     All Rights Reserved.                                             *
*                                                                      *
*                                                                      *
*     USeR Event INitialization: this routine is called before the     *
*     showering of an event is started, but after the source particles *
*     of that event have been already loaded on the stack              *
*                                                                      *
*     Created on 01 january 1991   by    Alfredo Ferrari & Paola Sala  *
*                                                   Infn - Milan       *
*                                                                      *
*     Last change on 09-apr-99     by    Alfredo Ferrari               *
*                                                                      *
*                                                                      *
*----------------------------------------------------------------------*
*
      INCLUDE '(IMGDRAW)'

C      WRITE(*,*) 'usrein'
C      NeuNum,IsoNum,
C     &MuInitT, MuInitE,MuInitP,MuInitTP,
C     &OwsInitP,IwsInitP,MoInitP,LsInitP,GdInitP,
C     &OwsFinaP,IwsFinaP,MoFinaP,LsFinaP,GdFinaP,
C     &NeuInitT, NeuInitE,NeuInitP,NeuCapP,NeuGamaN,NeuGamaT,NeuGamaE,
C     &NeuMaID,NeuType=0
*muon
      NeuNum=0 
      IsoNum=0 
      MuInitT=0 
      MuInitE=0 
      MuInitP=0 
      MuInitTP=0 
      OwsInitP=0 
      IwsInitP=0 
      MoInitP=0 
      LsInitP=0 
      GdInitP=0 
      OwsLen=0
      IwsLen=0
      MoLen=0
      LsLen=0
      GdLen=0
*neutron
      NeuInitT=0 
      NeuInitE=0 
      NeuInitP=0 
      NeuCapP=100000 
      NeuCapT=0 
      NeuGamaN=0 
      NeuGamaE=0
      NeuMaID=0 
      NeuType=0
      NeuCapVm=0
      NeuCapTn=0
      MaxNeuE=0
      NeuInitVm=0

*general
      NRGNAM='VACUUM'
      NowVol=2
      USDP=0
      USDVol=0

      RETURN
*=== End of subroutine Usrein =========================================*
      END


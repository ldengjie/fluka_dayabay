*----------------------------------------------------------------------*
*                                                                      *
*     MaGnetic field trajectory DRAWing: actually this entry manages   *
*                                        all trajectory dumping for    *
*                                        drawing                       *
*                                                                      *
*     Created on   21 Aug 2014     by   Li Dengjie                     *
*     Last change   *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
      SUBROUTINE MGDRAW ( ICODE, MREG )

      INCLUDE '(DBLPRC)'
      INCLUDE '(DIMPAR)'
      INCLUDE '(IOUNIT)'
*
      INCLUDE '(CASLIM)'
      INCLUDE '(COMPUT)'
      INCLUDE '(SOURCM)'
      INCLUDE '(FHEAVY)'
      INCLUDE '(FLKSTK)'
      INCLUDE '(GENSTK)'
      INCLUDE '(MGDDCM)'
      INCLUDE '(PAPROP)'
      INCLUDE '(QUEMGD)'
      INCLUDE '(SUMCOU)'
      INCLUDE '(TRACKR)'
*
      INCLUDE '(IMGDRAW)'
      INCLUDE '(BLNKCM)'
      INCLUDE '(LOWNEU)'
      INCLUDE '(RESNUC)'
      INCLUDE '(EVTFLG)'

      DIMENSION KA (4), KZ (4), BRDAUG (4), T12DAU (4),D2P(3)
      DOUBLE PRECISION HafTime
*
      DIMENSION DTQUEN ( MXTRCK, MAXQMG )
*
      EXTERNAL TIM1O2, BDNOPT

*get neutron initial energy at this neutron's first MGDRAW call
      if(JTRACK.EQ.8) then
       if(ISPUSR(3).ne.0) then
        if(NeuInitE(ISPUSR(3)) .eq. 0) then
         IF (KTRACK.GT.0) THEN 
*Randomly distribute the neutron energy in the group <20MeV 
            ALOGEA = LOG (GMSTOR(IDXSEC+KTRACK+1)) ! Lower bin boundary 
            ALOGEB = LOG (GMSTOR(IDXSEC+KTRACK)) ! Higher bin boundary 
            NeuInitE(ISPUSR(3))= 
     &EXP(ALOGEA+FLRNDM(DUMMY)*(ALOGEB-ALOGEA)) 
         ELSE
            NeuInitE(ISPUSR(3))=ETRACK-AM(8)
         ENDIF 
         NeuInitC(ISPUSR(3),1:3)=[CXTRCK,CYTRCK,CZTRCK]
        endif
       else
C      WRITE(*,*) 'error:ISPUSR(3).eq.0'
       endif
      endif
      RETURN

*  +-------------------------------------------------------------------*
      ENTRY BXDRAW ( ICODE, MREG, NEWREG, XSCO, YSCO, ZSCO )

      RETURN

*  +-------------------------------------------------------------------*
      ENTRY EEDRAW ( ICODE ) 
*neutron

      if(NeuNum.gt.0) then
C          DO I=1,NeuNum
          DO I=1,1
          if(NeuInitE(I).eq.0) then
             WRITE(*,*) 'Error:NeuInitE(I).eq.0'
          else
C        WRITE(*,*) I,NeuInitE(I)
        call fillneu(NCASE,NeuInitE(I),NeuInitT(I)*1.e9,
     &NeuInitP(I,1),NeuInitP(I,2),NeuInitP(I,3),
     &NeuInitC(I,1),NeuInitC(I,2),NeuInitC(I,3),
     &NeuCapP(I,1),NeuCapP(I,2),NeuCapP(I,3),
     &NeuCapT(I)*1.e9,NeuGamaE(I),NeuGamaN(I),
     &NeuMaID(I),NeuType(I),NeuCapVm(I),NeuCapTn(I),
     &NeuInitVm(I),NeuMaE(I),NeuDauVm(I))
         endif
          enddo
      endif

      RETURN

*  +-------------------------------------------------------------------*
      ENTRY ENDRAW ( ICODE, MREG, RULL, XSCO, YSCO, ZSCO )

      RETURN

*  +-------------------------------------------------------------------*
      ENTRY SODRAW
        WRITE(*,*) 'SODRAW'
                NeuInitE(1)=TKEFLK(1)
                NeuInitP(1,1:3)=[XFLK(1),YFLK(1),ZFLK(1)]
                NeuInitC(1,1:3)=[TXFLK(1),TYFLK(1),TZFLK(1)]
      RETURN

*  +-------------------------------------------------------------------*
      ENTRY USDRAW ( ICODE, MREG, XSCO, YSCO, ZSCO )

*neutron
* ISPUSR 1.reaction type 2.parent'd id 3.neutron num 4.isotopes num 5.initial volume 6.initial volume of muon's daughter ?.gamma num 
      ISPUSR(1)=ICODE
      ISPUSR(2)=JTRACK
C      if(JTRACK.eq.7) then
C          WRITE(*,*) 'gamma Reaction Type',ICODE
C      endif
      NowVol=MREG
* SPAUSR 1.parent's age 2.parent's energy
      SPAUSR(1)=ATRACK
      if(JTRACK.lt.200 .and. JTRACK.gt.0) then
          SPAUSR(2)=ETRACK-AM(JTRACK)
      else
          SPAUSR(2)=10000
      endif
*
      USDP(1)=XSCO 
      USDP(2)=YSCO 
      USDP(3)=ZSCO 
      USDVol=MREG
      USDDauVm=ISPUSR(6)


*find maximum energy of secondary neutron
      if(JTRACK.eq.8 ) then
         SecNeuNO=0
         MaxNeuE=0
         do I=1,NP
            if(KPART(I).eq.8) then
               SecNeuNO=SecNeuNO+1
               if(MaxNeuE.lt.TKI(I)) MaxNeuE=TKI(I)
            endif
         enddo
      endif

*neutron capture
      if(JTRACK.eq.8 .and. ICODE.eq.300)then
          OnlyGamm=0
          DO IP = 1, NP 
             if(KPART(IP).ne.7) then
                 OnlyGamm=0
                 exit
             else
                 OnlyGamm=OnlyGamm+1
             endif
          END DO 
          if(OnlyGamm.ge.1) then
            if(ISPUSR(3).ne.0) then
              NeuGamaE(ISPUSR(3))=0
              NeuGamaN(ISPUSR(3))=0
             DO IP = 1, NP 
                 if(KPART(IP).eq.7) then
                     NeuGamaN(ISPUSR(3))=NeuGamaN(ISPUSR(3))+1
                     NeuGamaE(ISPUSR(3))=NeuGamaE(ISPUSR(3))+TKI (IP)
                     NeuCapT(ISPUSR(3))=AGESEC(IP)+ATRACK !usually AGESEC(IP)==0
                     NeuCapP(ISPUSR(3),1:3)=[XSCO,YSCO,ZSCO]
                     NeuCapVm(ISPUSR(3))=MREG
                     NeuCapTn(ISPUSR(3))=MMTRCK
                 endif
             END DO 
C             WRITE(*,*) 'Neutron captured on :',MMTRCK
            endif
          endif
      endif
      RETURN
*=== End of subrutine Mgdraw ==========================================*
      END


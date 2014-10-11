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

      DIMENSION KA (4), KZ (4), BRDAUG (4), T12DAU (4)
      DOUBLE PRECISION HafTime
*
      DIMENSION DTQUEN ( MXTRCK, MAXQMG )
*
      EXTERNAL TIM1O2, BDNOPT

C      if(MREG.eq.10 .or. MREG.eq.12) then
C         DO I=1,MTRACK
C            if(DTRACK (I).gt.0) then
C                IICode=0
C                if(LTRACK.gt.1) then
C                    ISpaMaId=ISPUSR(2)
C                    ISpaMaTy=ISPUSR(1)
C                else
C                    ISpaMaId=0
C                    ISpaMaTy=0
C                endif
C*  |  Quenching is activated
C                IF ( LQEMGD ) THEN
C                   IF ( MTRACK .GT. 0 ) THEN
C                      QenE=0
C                      RULLL  = ZERZER
C                      CALL QUENMG ( ICODE, MREG, RULLL, DTQUEN )
C                      if(ZFRTTK.gt.1.5) then
C                          JBK=2
C                      else
C                          JBK=1
C                      endif
C                      DO J=1,MTRACK
C                          QenE=QenE+DTQUEN(J,JBK)
C                      ENDDO
C                   END IF
C                END IF
C*  |  End of quenching
C
C               call fillspa(NCASE,XTRACK (I),YTRACK (I),ZTRACK (I),
C     &DTRACK (I),ATRACK,QenE,JTRACK,IICode,ISpaMaId,ISpaMaTy,
C     &MREG,ISPUSR(5))
C            endif
C         ENDDO
C      endif

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
        endif
       else
      WRITE(*,*) 'error:ISPUSR(3).eq.0'
       endif
      endif

      RETURN

*  +-------------------------------------------------------------------*
      ENTRY BXDRAW ( ICODE, MREG, NEWREG, XSCO, YSCO, ZSCO )
      if(LTRACK.eq.1) then
      CALL GEOR2N ( MREG,MRGNAM,IERR1)
      CALL GEOR2N ( NEWREG,NRGNAM,IERR2)
C              WRITE(*,*) MRGNAM,'->',NRGNAM
      
          IF(DOT_PRODUCT(DetInitP(NEWREG,1:3),DetInitP(NEWREG,1:3))
     &       .eq.0) then
              DetInitP(NEWREG,1:3)=[XSCO, YSCO, ZSCO]
          else
              WRITE(*,*) 'ERROR : DetInitP .NE. 0',NEWREG
          end if

          DetLen(MREG)=DetLen(MREG)+sqrt(
     &                 (XSCO-DetInitP(MREG,1))*(XSCO-DetInitP(MREG,1))+
     &                 (YSCO-DetInitP(MREG,2))*(YSCO-DetInitP(MREG,2))+
     &                 (ZSCO-DetInitP(MREG,3))*(ZSCO-DetInitP(MREG,3)))
C              WRITE(*,*) 'DetLen(',MREG,') : ',DetLen(MREG)
          DetInitP(MREG,1:3)=0
      endif

      RETURN

*  +-------------------------------------------------------------------*
      ENTRY EEDRAW ( ICODE ) 
*muon 
      call fillmuon(NCASE,MuCharge,MuInitE,MuInitT,MuInitP(1),
     &MuInitP(2),MuInitP(3),
     &MuInitTP(1),MuInitTP(2),MuInitTP(3),DetLen(3),DetLen(4),
     &DetLen(5),DetLen(6),DetLen(7),DetLen(8),DetLen(9),DetLen(10),
     &DetLen(11),DetLen(12),NeuNum,IsoNum)
*neutron
      WRITE(*,*) 'fillneu'

      if(NeuNum.gt.0) then
          DO I=1,NeuNum
          if(NeuInitE(I).eq.0) then
             WRITE(*,*) 'Error:NeuInitE(I).eq.0'
          else
        WRITE(*,*) I,NeuInitE(I)
        call fillneu(NCASE,NeuInitE(I),NeuInitT(I),
     &NeuInitP(I,1),NeuInitP(I,2),NeuInitP(I,3),
     &NeuCapP(I,1),NeuCapP(I,2),NeuCapP(I,3),
     &NeuCapT(I),NeuGamaE(I),NeuGamaN(I),
     &NeuMaID(I),NeuType(I),NeuCapVm(I),NeuCapTn(I),
     &NeuInitVm(I),NeuMaE(I))
         endif
          enddo
      endif
      RETURN

*  +-------------------------------------------------------------------*
      ENTRY ENDRAW ( ICODE, MREG, RULL, XSCO, YSCO, ZSCO )
C      if(MREG.eq.10 .or. MREG.eq.12) then
C                IICode=ICODE
C                if(LTRACK.gt.1) then
C                    ISpaMaId=ISPUSR(2)
C                    ISpaMaTy=ISPUSR(1)
C                else
C                    ISpaMaId=0
C                    ISpaMaTy=0
C                endif
C*  |  Quenching is activated : calculate quenching factor
C*  |  and store quenched energy in DTQUEN(1, jbk)
C                IF ( LQEMGD ) THEN
C                      QenE=0
C                   RULLL = RULL
C                   CALL QUENMG ( ICODE, MREG, RULLL, DTQUEN )
C                END IF
C                      if(ZFRTTK.gt.1.5) then
C                          JBK=2
C                      else
C                          JBK=1
C                      endif
C                      QenE=QenE+DTQUEN(1,JBK)
C*  |  end quenching
C               call fillspa(NCASE,XSCO,YSCO,ZSCO,
C     &RULL,ATRACK,QenE,JTRACK,IICode,ISpaMaId,ISpaMaTy,MREG,ISPUSR(5))
C      endif

      RETURN

*  +-------------------------------------------------------------------*
      ENTRY SODRAW
      MuInitT=AGESTK(1)
      MuInitE=TKEFLK(1)
      MuInitP=[XFLK(1),YFLK(1),ZFLK(1)]
      MuInitTP=[TXFLK(1),TYFLK(1),TZFLK(1)]
      if(ILOFLK(1).eq.10) then
         MuCharge=1
      else
         MuCharge=-1
      endif
      EvtID=NCASE

      RETURN

*  +-------------------------------------------------------------------*
      ENTRY USDRAW ( ICODE, MREG, XSCO, YSCO, ZSCO )

*neutron
* ISPUSR 1.reaction type 2.parent'd id 3.neutron num 4.isotopes num 5.initial volume ?.gamma num 
      ISPUSR(1)=ICODE
      ISPUSR(2)=JTRACK
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
*find maximum energy of secondary neutron
      if(JTRACK.eq.8 .and. ICODE.eq.101) then
         SecNeuNO=0
         MaxNeuE=0
         do I=1,NP
            if(KPART(I).eq.8) then
               SecNeuNO=SecNeuNO+1
               if(MaxNeuE.lt.TKI(I)) MaxNeuE=TKI(I)
            endif
         enddo
C         do I=1,NP
C            if(KPART(I).eq.8) then
C             if(TKI(I).ne.MaxNeuE) then
C                 WRITE(*,*) 'USDRAW(',NeuNum,') : find a neutron ',
C     &'TKI(I):MaxNeuE',TKI(I),MaxNeuE,'mother:',JTRACK
C             endif
C            endif
C         enddo
C      endif
C      if(JTRACK.ne.8)then
C         do I=1,NP
C            if(KPART(I).eq.8) then
C                 WRITE(*,*) 'USDRAW(',NeuNum,') : find a neutron ',
C     &'TKI(I):',TKI(I),'mother:',JTRACK
C            endif
C         enddo
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

*Michel electron
      if((JTRACK.eq.10 .or. JTRACK.eq.11) .and. ICODE.eq.102) then
          DO IP = 1, NP 
             if(KPART(IP).eq.3) then
      call fillmi(NCASE,TKI(IP),AGESEC(IP)+ATRACK,XSCO,YSCO,ZSCO,MREG)
             endif
          END DO 
          
      endif

      RETURN
*=== End of subrutine Mgdraw ==========================================*
      END


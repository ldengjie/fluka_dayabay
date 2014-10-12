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

C      WRITE(*,*) 'MGDRAW'
      if(MREG.eq.10 .or. MREG.eq.12) then
         DO I=1,MTRACK
            if(DTRACK (I).gt.0) then
                IICode=0
                if(LTRACK.gt.1) then
                    ISpaMaId=ISPUSR(2)
                    ISpaMaTy=ISPUSR(1)
                else
                    ISpaMaId=0
                    ISpaMaTy=0
                endif
*  |  Quenching is activated
                IF ( LQEMGD ) THEN
                   IF ( MTRACK .GT. 0 ) THEN
                      QenE=0
                      RULLL  = ZERZER
                      CALL QUENMG ( ICODE, MREG, RULLL, DTQUEN )
                      if(ZFRTTK.gt.1.5) then
                          JBK=2
                      else
                          JBK=1
                      endif
                      DO J=1,MTRACK
                          QenE=QenE+DTQUEN(J,JBK)
                      ENDDO
                   END IF
                END IF
*  |  End of quenching

               call fillspa(NCASE,XTRACK (I),YTRACK (I),ZTRACK (I),
     &DTRACK (I),ATRACK,QenE,JTRACK,IICode,ISpaMaId,ISpaMaTy,
     &MREG,ISPUSR(5))
            endif
         ENDDO
      endif

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
* get muon final volume and position
      MuFinalV=MREG
      MuFinalP=[XTRACK (NTRACK),YTRACK (NTRACK),ZTRACK (NTRACK)]
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
      if(MuFinalV>1) then
          IF(DOT_PRODUCT(DetInitP(MuFinalV,1:3),DetInitP(MuFinalV,1:3))
     &       .eq.0) then
          DetLen(MuFinalV)=DetLen(MuFinalV)+sqrt(
     &(MuFinalP(1)-DetInitP(MuFinalV,1))*
     &(MuFinalP(1)-DetInitP(MuFinalV,1))+
     &(MuFinalP(2)-DetInitP(MuFinalV,2))*
     &(MuFinalP(2)-DetInitP(MuFinalV,2))+
     &(MuFinalP(3)-DetInitP(MuFinalV,3))*
     &(MuFinalP(3)-DetInitP(MuFinalV,3)))
          DetInitP(MuFinalV,1:3)=0
          endif
      endif 

      call fillmuon(NCASE,MuCharge,MuInitE,MuInitT,MuInitP(1),
     &MuInitP(2),MuInitP(3),
     &MuInitTP(1),MuInitTP(2),MuInitTP(3),DetLen(3),DetLen(4),
     &DetLen(5),DetLen(6),DetLen(7),DetLen(8),DetLen(9),DetLen(10),
     &DetLen(11),DetLen(12),NeuNum,IsoNum)
*neutron
C      WRITE(*,*) 'fillneu'

      if(NeuNum.gt.0) then
          DO I=1,NeuNum
          if(NeuInitE(I).eq.0) then
             WRITE(*,*) 'Error:NeuInitE(I).eq.0'
          else
C        WRITE(*,*) I,NeuInitE(I)
        call fillneu(NCASE,NeuInitE(I),NeuInitT(I),
     &NeuInitP(I,1),NeuInitP(I,2),NeuInitP(I,3),
     &NeuCapP(I,1),NeuCapP(I,2),NeuCapP(I,3),
     &NeuCapT(I),NeuGamaE(I),NeuGamaN(I),
     &NeuMaID(I),NeuType(I),NeuCapVm(I),NeuCapTn(I),
     &NeuInitVm(I),NeuMaE(I),NeuDauVm(I))
C      WRITE(*,*) I,NeuDauVm(I)
         endif
          enddo
      endif

C      WRITE(*,*) 'MuFinalV',MuFinalV
C      DO i=1,15
C         if(DetLen(i).ne.0) WRITE(*,*) I,DetLen(i)
C      ENDDO
      RETURN

*  +-------------------------------------------------------------------*
      ENTRY ENDRAW ( ICODE, MREG, RULL, XSCO, YSCO, ZSCO )
      if(MREG.eq.10 .or. MREG.eq.12) then
                IICode=ICODE
                if(LTRACK.gt.1) then
                    ISpaMaId=ISPUSR(2)
                    ISpaMaTy=ISPUSR(1)
                else
                    ISpaMaId=0
                    ISpaMaTy=0
                endif
*  |  Quenching is activated : calculate quenching factor
*  |  and store quenched energy in DTQUEN(1, jbk)
                IF ( LQEMGD ) THEN
                      QenE=0
                   RULLL = RULL
                   CALL QUENMG ( ICODE, MREG, RULLL, DTQUEN )
                END IF
                      if(ZFRTTK.gt.1.5) then
                          JBK=2
                      else
                          JBK=1
                      endif
                      QenE=QenE+DTQUEN(1,JBK)
*  |  end quenching
               call fillspa(NCASE,XSCO,YSCO,ZSCO,
     &RULL,ATRACK,QenE,JTRACK,IICode,ISpaMaId,ISpaMaTy,MREG,ISPUSR(5))
      endif

      RETURN

*  +-------------------------------------------------------------------*
      ENTRY SODRAW
      MuInitT=AGESTK(1)
      MuInitE=TKEFLK(1)
      MuInitP=[XFLK(1),YFLK(1),ZFLK(1)]
      MuInitTP=[TXFLK(1),TYFLK(1),TZFLK(1)]
      DetInitP(2,1:3)=[XFLK(1),YFLK(1),ZFLK(1)]
      if(ILOFLK(1).eq.10) then
         MuCharge=1
      else
         MuCharge=-1
      endif
      EvtID=NCASE
C      WRITE(*,*) ''
C      WRITE(*,*) 'SODRAW',NCASE

      RETURN

*  +-------------------------------------------------------------------*
      ENTRY USDRAW ( ICODE, MREG, XSCO, YSCO, ZSCO )

*neutron
* ISPUSR 1.reaction type 2.parent'd id 3.neutron num 4.isotopes num 5.initial volume 6.initial volume of muon's daughter ?.gamma num 
      ISPUSR(1)=ICODE
      ISPUSR(2)=JTRACK
      if(LTRACK.eq.1) then 
         ISPUSR(6)=MREG
      endif
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
      if(JTRACK.eq.8 .and. ICODE.eq.101) then
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


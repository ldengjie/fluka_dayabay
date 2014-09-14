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
      INCLUDE '(IMGDRAW)'
      INCLUDE '(BLNKCM)'
      INCLUDE '(LOWNEU)'

      DIMENSION KA (4), KZ (4), BRDAUG (4), T12DAU (4)
      DOUBLE PRECISION HafTime
*
      DIMENSION DTQUEN ( MXTRCK, MAXQMG )
*
      EXTERNAL TIM1O2, BDNOPT

      if(NRGNAM.eq.'LS'.or.NRGNAM.eq.'GDLS') then
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

      RETURN

*  +-------------------------------------------------------------------*
      ENTRY BXDRAW ( ICODE, MREG, NEWREG, XSCO, YSCO, ZSCO )
      CALL GEOR2N ( MREG,MRGNAM,IERR1)
      CALL GEOR2N ( NEWREG,NRGNAM,IERR2)
      IF (NRGNAM.EQ.'OWS') THEN
          IF(DOT_PRODUCT(OwsInitP(1,1:3),OwsInitP(1,1:3)).eq.0) then
              OwsInitP(1,1:3)=[XSCO, YSCO, ZSCO]
          else
              OwsInitP(2,1:3)=[XSCO, YSCO, ZSCO]
          end if
      ELSE IF(NRGNAM.EQ.'IWS') THEN
          IF(DOT_PRODUCT(IwsInitP(1,1:3),IwsInitP(1,1:3)).EQ.0) then
              IwsInitP(1,1:3)=[XSCO, YSCO, ZSCO]
          else
              IwsInitP(2,1:3)=[XSCO, YSCO, ZSCO]
          end if
      ELSE IF(NRGNAM.EQ.'MO') THEN
          IF(DOT_PRODUCT(MoInitP(1,1:3),MoInitP(1,1:3)).EQ.0) then
              MoInitP(1,1:3)=[XSCO, YSCO, ZSCO]
          else
              MoInitP(2,1:3)=[XSCO, YSCO, ZSCO]
          end if
      ELSE IF(NRGNAM.EQ.'LS') THEN
          IF(DOT_PRODUCT(LsInitP(1,1:3),LsInitP(1,1:3)).EQ.0) then
              LsInitP(1,1:3)=[XSCO, YSCO, ZSCO]
          else
              LsInitP(2,1:3)=[XSCO, YSCO, ZSCO]
          end if
      ELSE IF(NRGNAM.EQ.'GDLS') THEN
          IF(DOT_PRODUCT(GdInitP(1,1:3),GdInitP(1,1:3)).EQ.0) then
              GdInitP(1,1:3)=[XSCO, YSCO, ZSCO]
          else
              GdInitP(2,1:3)=[XSCO, YSCO, ZSCO]
          end if
      ELSE

      END IF

      IF (MRGNAM.EQ.'OWS') THEN
          IF(DOT_PRODUCT(OwsFinaP(1,1:3),OwsFinaP(1,1:3)).EQ.0) then
              OwsFinaP(1,1:3)=[XSCO, YSCO, ZSCO]
          else
              OwsFinaP(2,1:3)=[XSCO, YSCO, ZSCO]
          end if
      ELSE IF(MRGNAM.EQ.'IWS') THEN
          IF(DOT_PRODUCT(IwsFinaP(1,1:3),IwsFinaP(1,1:3)).EQ.0) then
              IwsFinaP(1,1:3)=[XSCO, YSCO, ZSCO]
          else
              IwsFinaP(2,1:3)=[XSCO, YSCO, ZSCO]
          end if
      ELSE IF(MRGNAM.EQ.'MO') THEN
          IF(DOT_PRODUCT(MoFinaP(1,1:3),MoFinaP(1,1:3)).EQ.0) then
              MoFinaP(1,1:3)=[XSCO, YSCO, ZSCO]
          else
              MoFinaP(2,1:3)=[XSCO, YSCO, ZSCO]
          end if
      ELSE IF(MRGNAM.EQ.'LS') THEN
          IF(DOT_PRODUCT(LsFinaP(1,1:3),LsFinaP(1,1:3)).EQ.0) then
              LsFinaP(1,1:3)=[XSCO, YSCO, ZSCO]
          else
              LsFinaP(2,1:3)=[XSCO, YSCO, ZSCO]
          end if
      ELSE IF(MRGNAM.EQ.'GDLS') THEN
          IF(DOT_PRODUCT(GdFinaP(1,1:3),GdFinaP(1,1:3)).EQ.0) then
              GdFinaP(1,1:3)=[XSCO, YSCO, ZSCO]
          else
              GdFinaP(2,1:3)=[XSCO, YSCO, ZSCO]
          end if
      ELSE
      END IF

      RETURN

*  +-------------------------------------------------------------------*
      ENTRY EEDRAW ( ICODE )
*muon
      OwsLen=sqrt(DOT_PRODUCT(OwsFinaP(1,1:3)-OwsInitP(1,1:3),
     &OwsFinaP(1,1:3)-OwsInitP(1,1:3)))+sqrt(DOT_PRODUCT(
     &OwsFinaP(2,1:3)-OwsInitP(2,1:3),OwsFinaP(2,1:3)-OwsInitP(2,1:3)))
      IwsLen=sqrt(DOT_PRODUCT(IwsFinaP(1,1:3)-IwsInitP(1,1:3),
     &IwsFinaP(1,1:3)-IwsInitP(1,1:3)))+sqrt(DOT_PRODUCT(
     &IwsFinaP(2,1:3)-IwsInitP(2,1:3),IwsFinaP(2,1:3)-IwsInitP(2,1:3)))
      MoLen=sqrt(DOT_PRODUCT(MoFinaP(1,1:3)-MoInitP(1,1:3),
     &MoFinaP(1,1:3)-MoInitP(1,1:3)))+sqrt(DOT_PRODUCT(
     &MoFinaP(2,1:3)-MoInitP(2,1:3),MoFinaP(2,1:3)-MoInitP(2,1:3)))
      LsLen=sqrt(DOT_PRODUCT(LsFinaP(1,1:3)-LsInitP(1,1:3),
     &LsFinaP(1,1:3)-LsInitP(1,1:3)))+sqrt(DOT_PRODUCT(
     &LsFinaP(2,1:3)-LsInitP(2,1:3),LsFinaP(2,1:3)-LsInitP(2,1:3)))
      GdLen=sqrt(DOT_PRODUCT(GdFinaP(1,1:3)-GdInitP(1,1:3),
     &GdFinaP(1,1:3)-GdInitP(1,1:3)))+sqrt(DOT_PRODUCT(
     &GdFinaP(2,1:3)-GdInitP(2,1:3),GdFinaP(2,1:3)-GdInitP(2,1:3)))

      call fillmuon(NCASE,MuCharge,MuInitE,MuInitT,MuInitP(1),
     &MuInitP(2),MuInitP(3),
     &MuInitTP(1),MuInitTP(2),MuInitTP(3),OwsLen,IwsLen,MoLen,
     &LsLen,GdLen,
     &NeuNum,IsoNum)
*neutron
      if(NeuNum.gt.0) then
          DO I=1,NeuNum
          if(NeuInitE(I).eq.0) then
C             WRITE(*,*) 'Error:NeuInitE(I).eq.0'
          else
        call fillneu(NCASE,NeuInitE(I),NeuInitT(I),
     &NeuInitP(I,1),NeuInitP(I,2),NeuInitP(I,3),
     &NeuCapP(I,1),NeuCapP(I,2),NeuCapP(I,3),
     &NeuCapT(I),NeuGamaE(I),NeuGamaN(I),
     &NeuMaID(I),NeuType(I),NeuCapVm(I),NeuCapTn(I),
     &NeuInitVm)
         endif
          enddo
      endif
      RETURN

*  +-------------------------------------------------------------------*
      ENTRY ENDRAW ( ICODE, MREG, RULL, XSCO, YSCO, ZSCO )
      if(NRGNAM.eq.'LS'.or.NRGNAM.eq.'GDLS') then
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
      if(ILOFLK(1).eq.10) then
         MuCharge=1
      else
         MuCharge=-1
      endif
      EvtID=NCASE

      RETURN

*  +-------------------------------------------------------------------*
      ENTRY USDRAW ( ICODE, MREG, XSCO, YSCO, ZSCO )
C      WRITE(*,*) ''

*neutron
* ISPUSR 1.reaction type 2.parent'd id 3.neutron num 4.isotopes num 5.initial volume ?.gamma num 
      ISPUSR(1)=ICODE
      ISPUSR(2)=JTRACK
      NowVol=MREG
* SPAUSR 1.parent's age
      SPAUSR(1)=ATRACK
*find maximum energy of secondary neutron
      if(ICODE.eq.101 .and. JTRACK.eq.8) then
         SecNeuNO=0
         MaxNeuE=0
         do I=1,NP
            if(KPART(I).eq.8) then
               SecNeuNO=SecNeuNO+1
               if(MaxNeuE.lt.TKI(I)) MaxNeuE=TKI(I)
C               WRITE(*,*) 'MaxNeuE',MaxNeuE
            endif
         enddo
      endif
C               WRITE(*,*) 'MaxNeuE',MaxNeuE

*get neutron initial energy at first USDRAW call
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
C      WRITE(*,*) 'JTRACK',JTRACK
       endif
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
      if(LTRACK.eq.1 .and. ICODE.eq.102) then
          DO IP = 1, NP 
             if(KPART(IP).eq.3) then
      call fillmi(NCASE,TKI(IP),AGESEC(IP)+ATRACK,XSCO,YSCO,ZSCO,MREG)
             endif
          END DO 
          
      endif

      RETURN
*=== End of subrutine Mgdraw ==========================================*
      END


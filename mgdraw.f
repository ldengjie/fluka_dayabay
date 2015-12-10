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
C     &DTRACK (I),ATRACK*1.e9,QenE,JTRACK,IICode,ISpaMaId,ISpaMaTy,
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
         NeuInitC(ISPUSR(3),1:3)=[CXTRCK,CYTRCK,CZTRCK]
        endif
       else
      WRITE(*,*) 'error:ISPUSR(3).eq.0'
       endif
      endif
* get muon final volume and position
      if(LTRACK.eq.NowGen .and. JTRACK.EQ.MuId) then
         MuFinalV=MREG
         MuFinalP(1:3)=[XTRACK(NTRACK),YTRACK(NTRACK),ZTRACK(NTRACK)]
      endif
      RETURN

*  +-------------------------------------------------------------------*
      ENTRY BXDRAW ( ICODE, MREG, NEWREG, XSCO, YSCO, ZSCO )
      if(LTRACK.eq.NowGen .and. JTRACK.EQ.MuId) then
C      CALL GEOR2N ( MREG,MRGNAM,IERR1)
C      CALL GEOR2N ( NEWREG,NRGNAM,IERR2)
C              WRITE(*,*) MRGNAM,'->',NRGNAM,XSCO, YSCO, ZSCO
C      if(NEWREG.eq.10) then
C      WRITE(*,*) 'MuInitTP', MuInitTP(1),MuInitTP(2),MuInitTP(3)
C          WRITE(*,*) 'LSPosIn',XSCO, YSCO, ZSCO
C          Dtx=XSCO-MuInitP(1)
C          Dty=YSCO-MuInitP(2)
C          Dtz=ZSCO-MuInitP(3)
C          Dtl=SQRT(Dtx*Dtx+Dty*Dty+Dtz*Dtz)
C          WRITE(*,*) 'Cos',Dtx/Dtl,Dty/Dtl,Dtz/Dtl
C      endif
C      if(MREG.eq.10) then
C          WRITE(*,*) 'LSPosOut',XSCO, YSCO, ZSCO
C      endif
      
C          IF(DOT_PRODUCT(DetInitP(NEWREG,1:3),DetInitP(NEWREG,1:3))
C     &       .eq.0) then
          if(IfDetIP(NEWREG).eq.0) then
              DetInitP(NEWREG,1:3)=[XSCO, YSCO, ZSCO]
              IfDetIP(NEWREG)=1
          else
              WRITE(*,*) 'ERROR : DetInitP .NE.  0',NEWREG,
     &'IfDetIP',IfDetIP(NEWREG)
          end if
          
          if(MREG.ge.7) then
              if(XSCO.lt.0) then
                  NDet=1
              else
                  NDet=2
              endif
              if(YSCO.gt.300) then
                  NDet=NDet+2
              endif
          else
              NDet=1
          endif

          DetLen(MREG,NDet)=DetLen(MREG,NDet)+sqrt(
     &                 (XSCO-DetInitP(MREG,1))*(XSCO-DetInitP(MREG,1))+
     &                 (YSCO-DetInitP(MREG,2))*(YSCO-DetInitP(MREG,2))+
     &                 (ZSCO-DetInitP(MREG,3))*(ZSCO-DetInitP(MREG,3)))
C              WRITE(*,*) 'DetLen(',MREG,') : ',DetLen(MREG)
          DetInitP(MREG,1:3)=0
          IfDetIP(MREG)=0
      endif
C      if(JTRACK.eq.8) then
C          if(NEWREG.eq.1) then
C              NeuNum2=NeuNum2+1
C              WRITE(*,*) '  BXD NeuNum2:',NeuNum2,'ISPUSR(3):',
C     &ISPUSR(3),MREG,'->',NEWREG
C          endif
C      endif

      RETURN

*  +-------------------------------------------------------------------*
      ENTRY EEDRAW ( ICODE ) 
*muon 
      if(MuFinalV>1) then
C          if(MuFinalV.eq.3) then
C           WRITE(*,*) DetInitP(MuFinalV,1),'->',MuFinalP(1)
C           WRITE(*,*) DetInitP(MuFinalV,2),'->',MuFinalP(2)
C           WRITE(*,*) DetInitP(MuFinalV,3),'->',MuFinalP(3)
C           WRITE(*,*) 'IfDetIP(MuFinalV)',IfDetIP(MuFinalV)
C          endif
C          IF(DOT_PRODUCT(DetInitP(MuFinalV,1:3),DetInitP(MuFinalV,1:3))
C     &       .ne.0) then
          if(IfDetIP(MuFinalV).eq.1) then
          if(MuFinalV.ge.7) then
              if(MuFinalP(1).lt.0) then
                  NDet=1
              else
                  NDet=2
              endif
              if(MuFinalP(2).gt.300) then
                  NDet=NDet+2
              endif
          else
              NDet=1
          endif
          DetLen(MuFinalV,NDet)=DetLen(MuFinalV,NDet)+sqrt(
     &(MuFinalP(1)-DetInitP(MuFinalV,1))*
     &(MuFinalP(1)-DetInitP(MuFinalV,1))+
     &(MuFinalP(2)-DetInitP(MuFinalV,2))*
     &(MuFinalP(2)-DetInitP(MuFinalV,2))+
     &(MuFinalP(3)-DetInitP(MuFinalV,3))*
     &(MuFinalP(3)-DetInitP(MuFinalV,3)))
          DetInitP(MuFinalV,1:3)=0
          IfDetIP(MuFinalV)=0
          endif
      endif 
C          WRITE(*,*) 'MuFinalV,X,Y,Z',MuFinalV,MuFinalP(1),
C     &MuFinalP(2),MuFinalP(3)
C      DO i=1,15
C         if(DetLen(i).ne.0) WRITE(*,*) I,DetLen(i)
C      ENDDO

C      if(DetLen(10,1).gt.0 .or. DetLen(10,2).gt.0) then
C          WRITE(*,*) 'mLS',DetLen(10,1),DetLen(10,2)
C      endif
      call fillmuon(NCASE,MuCharge,MuInitE,MuInitT*1.e9,MuInitP(1),
     &MuInitP(2),MuInitP(3),
     &MuInitTP(1),MuInitTP(2),MuInitTP(3),DetLen(3,1),DetLen(4,1),
     &DetLen(5,1),DetLen(6,1),DetLen(7,1:4),DetLen(8,1:4),
     &DetLen(9,1:4),DetLen(10,1:4),
     &DetLen(11,1:4),DetLen(12,1:4),NeuNum,IsoNum,
     &MuFinalP(1),MuFinalP(2),MuFinalP(3),MuFinalV)
*neutron
C      if(NeuNum.gt.0 .or. NeuNum2.gt.0) then
C        WRITE(*,*) '>>>EEDRAW(',NCASE,') NeuNum:',NeuNum,
C     &' NeuNum2:',NeuNum2
C          DO I=1,NeuNum
C        WRITE(*,*) I,NeuInitE(I),NeuInitT(I),
C     &NeuInitP(I,1),NeuInitP(I,2),NeuInitP(I,3),
C     &NeuCapP(I,1),NeuCapP(I,2),NeuCapP(I,3),
C     &NeuCapT(I),NeuGamaE(I),NeuGamaN(I),
C     &NeuMaID(I),NeuType(I),NeuCapVm(I),NeuCapTn(I),
C     &NeuInitVm(I),NeuMaE(I),NeuDauVm(I)
C          enddo
C      endif

      if(NeuNum.gt.0) then
          DO I=1,NeuNum
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
C     &RULL,ATRACK*1.e9,QenE,JTRACK,IICode,ISpaMaId,
C     &ISpaMaTy,MREG,ISPUSR(5))
C      endif

      RETURN

*  +-------------------------------------------------------------------*
      ENTRY SODRAW
      MuInitT=AGESTK(1)
      MuInitE=TKEFLK(1)
      MuInitP=[XFLK(1),YFLK(1),ZFLK(1)]
      MuInitTP=[TXFLK(1),TYFLK(1),TZFLK(1)]
      DetInitP(2,1:3)=[XFLK(1),YFLK(1),ZFLK(1)]
      IfDetIP(2)=1
      if(ILOFLK(1).eq.10) then
         MuCharge=1
      else
         MuCharge=-1
      endif
      EvtID=NCASE
      MuId=ILOFLK(1)
CC Z
C      if(ZFLK(1).ge.3300)then
C          D2P=MuInitP+MuInitTP*(ZFLK(1)-3300)/(-MuInitTP(3))
CC          WRITE(*,*) 'MuInitP(3):D2P(3)',MuInitP(3),D2P(3)
C          if((D2P(1).le.1100 .and. (D2P(1).ge.(-1100))) .and.
C     &    (D2P(2).le.800 .and. (D2P(2).ge.(-800)))) then
C          WRITE(*,*) 'InitPZ',D2P(1),D2P(2),D2P(3)
C          endif
C      endif
CC X
C      if(MuInitTP(1).lt.0 .and. XFLK(1).ge.1100) then
C          D2P=MuInitP+MuInitTP*(XFLK(1)-1100)/(-MuInitTP(1))
C          if((D2P(3).le.3300 .and. (D2P(3).ge.(-3300))) .and.
C     &    (D2P(2).le.800 .and. (D2P(2).ge.(-800)))) then
C          WRITE(*,*) 'InitPX1',D2P(1),D2P(2),D2P(3)
C          endif
C      endif
C      if(MuInitTP(1).gt.0 .and. XFLK(1).le.-1100) then
C          D2P=MuInitP+MuInitTP*(-1100-XFLK(1))/MuInitTP(1)
C          if((D2P(3).le.3300 .and. (D2P(3).ge.(-3300))) .and.
C     &    (D2P(2).le.800 .and. (D2P(2).ge.(-800)))) then
C          WRITE(*,*) 'InitPX2',D2P(1),D2P(2),D2P(3)
C          endif
C      endif
CC Y
C      if(MuInitTP(2).lt.0 .and. YFLK(1).ge.800) then
C          D2P=MuInitP+MuInitTP*(YFLK(1)-800)/(-MuInitTP(2))
C          if((D2P(3).le.3300 .and. (D2P(3).ge.(-3300))) .and.
C     &    (D2P(1).le.1100 .and. (D2P(1).ge.(-1100)))) then
C          WRITE(*,*) 'InitPY1',D2P(1),D2P(2),D2P(3)
C          endif
C      endif
C      if(MuInitTP(2).gt.0 .and. YFLK(1).le.-800) then
C          D2P=MuInitP+MuInitTP*(-800-YFLK(1))/MuInitTP(2)
C          if((D2P(3).le.3300 .and. (D2P(3).ge.(-3300))) .and.
C     &    (D2P(1).le.1100 .and. (D2P(1).ge.(-1100)))) then
C          WRITE(*,*) 'InitPY2',D2P(1),D2P(2),D2P(3)
C          endif
C      endif
CC test if pass through LS
C      if(MuInitP(3).gt.200) then
C          D2P(1:3)=MuInitP(1:3)+(MuInitP(3)-200)*MuInitTP/(-MuInitTP(3))
C          if(((D2P(1)-300)*(D2P(1)-300)+D2P(2)*D2P(2)).le.40000 .or.
C     &((D2P(1)-(-300))*(D2P(1)-(-300))+D2P(2)*D2P(2)).le.40000) then
C              WRITE(*,*) 'bLS',D2P(1),D2P(2),D2P(3)
C          else
C      D2P(1:3)=MuInitP(1:3)+(MuInitP(3)-(-200))*MuInitTP/(-MuInitTP(3))
C          if(((D2P(1)-300)*(D2P(1)-300)+D2P(2)*D2P(2)).le.40000 .or.
C     &((D2P(1)-(-300))*(D2P(1)-(-300))+D2P(2)*D2P(2)).le.40000) then
C              WRITE(*,*) 'bLS',D2P(1),D2P(2),D2P(3)
C              endif
C          endif
C      endif
C      if(MuInitP(3).le.200 .and. MuInitP(3).ge.(-200)) then
C      D2P(1:3)=MuInitP(1:3)+(MuInitP(3)-(-200))*MuInitTP/(-MuInitTP(3))
C          if(((D2P(1)-300)*(D2P(1)-300)+D2P(2)*D2P(2)).le.40000 .or.
C     &((D2P(1)-(-300))*(D2P(1)-(-300))+D2P(2)*D2P(2)).le.40000) then
C              WRITE(*,*) 'bLS',D2P(1),D2P(2),D2P(3)
C              endif
C      endif
C
C      WRITE(*,*) 'SODRAW',NCASE

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
      if(LTRACK.eq.NowGen .and. JTRACK.EQ.MuId) then
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
C      if(JTRACK.eq.8 .and. ICODE.eq.101) then
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

C      NeuCount = 0
C      do  ip = 1, NP
C      IF (KPART(ip) .EQ. 8) THEN
C          NeuCount = NeuCount + 1
C      END IF
C      enddo 
C      IF (JTRACK .EQ. 8) THEN
C          NeuCount = NeuCount - 1
C      END IF
C      IF (NeuCount.GE.1) THEN
C          do  ip = 1, NP
C          IF (KPART(ip) .EQ. 8) THEN
C               WRITE(*, *) 'USDLI', NCASE, JTRACK, ICODE, TKI(ip)
C              IF (JTRACK .EQ. 8 .and. TKI(ip).ne.MaxNeuE) THEN
C                  WRITE(*, *) 'USSubOne', NCASE, JTRACK, ICODE, TKI(ip)
C              elseif(JTRACK.ne.8) then
C                  WRITE(*, *) 'USSubOne', NCASE, JTRACK, ICODE, TKI(ip)
C              ENDIF
C          END IF
C      enddo 
C       END IF


* Loop over Secondaries.
C      nn=0     
C      hikin=0
C      nocount=9999
C      do ip = 1, NP
C        if(kpart(ip).eq.8) nn=nn+1
C      enddo
C
C      if (nn.gt.0 .and. jtrack.eq.8) then
C          do ip=1,np
C            if(kpart(ip).eq.8 .and. tki(ip).gt.hikin) then 
C               nocount=ip
C               hikin=tki(ip)
C            endif
C          enddo 
C      do ip=1,np
C              if(ip.ne.nocount .and. kpart(ip).eq.8) then
C                  write(*,*) 'ye',icode, jtrack, xsco, ysco, zsco, 
C     +                          tki(ip), wei(ip),
C     +                          cxr(ip), cyr(ip), czr(ip)
C              endif
C          enddo  
C      else if (nn.gt.0) then 
C          do ip=1,np
C              if (kpart(ip).eq.8) then
C                  write(*,*) 'ye',icode, jtrack, xsco, ysco, zsco, 
C     +                          tki(ip), wei(ip),
C     +                          cxr(ip), cyr(ip), czr(ip)
C             endif
C          enddo
C      endif

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
      if(JTRACK.eq.MuId .and. ICODE.eq.102) then
          DO IP = 1, NP 
C             WRITE(*,*) '102:',MREG,XSCO,YSCO,ZSCO,KPART(IP),TKI(IP)
             if(KPART(IP).eq.3 .or. KPART(IP).eq.4) then
      call fillmi(NCASE,TKI(IP),(AGESEC(IP)+ATRACK)*1.e9,
     &XSCO,YSCO,ZSCO,MREG)
C             WRITE(*,*) 'fillmi :',LTRACK,MREG,XSCO,YSCO,ZSCO
             endif
          END DO 
          
      endif
C      if(JTRACK.eq.8) then
C          NoNeu=0
C          IsGa=1
C         do I=1,NP
C            if(KPART(I).eq.8) then
C                NoNeu=1
C            endif
C            if(KPART(I).ne.7) then
C                IsGa=0
C            endif
C         enddo
C          if(NoNeu.eq.0 .and. IsGa.eq.1 .and. NP.gt.0) then
C              NeuNum2=NeuNum2+1
C              WRITE(*,*) '  USD ',ICODE,' NeuNum2:',NeuNum2,
C     &'ISPUSR(3):',ISPUSR(3)
C         do I=1,NP
C                WRITE(*,*) '    ',KPART(I)
C         enddo
C          endif
C      endif

      if(LTRACK.eq.NowGen .and. JTRACK.EQ.MuId) then
C          WRITE(*,*) '   NowGen,ETRACK,ICODE,MREG,X,Y,Z',NowGen,ETRACK,
C     &ICODE,MREG,XSCO, YSCO, ZSCO 
          if(ICODE.eq.101)  then
C                WRITE (*,*) '== ICODE(',JTRACK,') : ',ICODE
C                WRITE(*,*) '*GENSTK'
                DO IP = 1, NP 
                    if(KPART(IP).eq.MuId) then
                        NowGen=NowGen+1
                        exit
                    endif
C                    WRITE(*,*) '+>',KPART(IP),ICODE,TKI (IP)
                END DO 
C                WRITE(*,*) '*FHEAVY'
C                DO IP = 1,NPHEAV 
C                    WRITE(*,*) '=>',KHEAVY(IP),TKHEAV(IP),AGHEAV(IP),
C     &                         ICHEAV(KHEAVY(IP)),IBHEAV(KHEAVY(IP)),
C     &                         ANHEAV(KHEAVY(IP))
C                END DO 
C                WRITE(*,*) '*RESNUC'
C                WRITE(*,*) ICESTR,IBESTR,'->',ICRES,IBRES,AMNRES,AMMRES
          endif
      endif

      RETURN
*=== End of subrutine Mgdraw ==========================================*
      END


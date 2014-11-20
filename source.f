*=== Source of muons at FAR     
*=== Auther  : lidengjie@ihep.ac.cn 
*=== Created : Thursday Aug 14 2014 
*
*=== source ===========================================================*
*
      SUBROUTINE SOURCE ( NOMORE )

      INCLUDE '(DBLPRC)'
      INCLUDE '(DIMPAR)'
      INCLUDE '(IOUNIT)'
*
      INCLUDE '(BEAMCM)'
      INCLUDE '(FHEAVY)'
      INCLUDE '(FLKSTK)'
      INCLUDE '(IOIOCM)'
      INCLUDE '(LTCLCM)'
      INCLUDE '(PAPROP)'
      INCLUDE '(SOURCM)'
      INCLUDE '(SUMCOU)'
      INCLUDE '(IMGDRAW)'
********************************************************************
*
*  SVecN  : normal vector of each surface
*  SPoMin : minimum point on the surface 
*  SLen   : length of each border of the surface
*  OPoMin : target origin's minimum point
*  OPoMax : target origin's maximum point
*  ProVec : incident particle's direction vector
*  ValidS : valid area of this surface which is perpendicular to ProVec
*  DIniPo : initial incident point
*  SecTag : whether is valid surface (ValidS>0)
*  PRVec  : random vector used for getting initial point
*
********************************************************************
      LOGICAL LFIRST
      DATA LFIRST / .TRUE. /
      DATA ISrsNum / 0 /
*
      PARAMETER(NLINES = 1000000,MaxP=5)
      DIMENSION Enrgy(NLINES), Theta(NLINES), Phi(NLINES),
     &          SVecN(MaxP,3),SPoMin(MaxP,3),SLen(MaxP,3)
      SAVE LFIRST, Enrgy, Theta, Phi, SVecN,SPoMin, SLen
*
      DIMENSION OPoMin(3),OPoMax(3),ProVec(3),ValidS(MaxP),
     &          DIniPo(3),SecTag(MaxP),PRVec(3)
*
*======================================================================*
      NOMORE = 0
*  +-------------------------------------------------------------------*
*
*     First call initializations:
      IF ( LFIRST ) THEN
*     *** The following 3 cards are mandatory ***
         TKESUM = ZERZER
         LFIRST = .FALSE.
         LUSSRC = .TRUE.
*     *** User initialization ***
        OPEN(UNIT=88,FILE="/afs/ihep.ac.cn/users/l/lidj/largedata/flukaW
     &ork/FAR/mountain.FAR",STATUS="OLD")
        DO I = 1, NLINES
           READ(88,*) Enrgy(I),Theta(I),Phi(I)
C           IF(I .LE. 50) THEN
C               WRITE(LUNOUT,*) I,Enrgy(I),Theta(I),Phi(I)
C           END IF
        END DO
        CLOSE(88)
        OPEN(UNIT=89,FILE="../NextSeedNum",STATUS="OLD")
           READ(89,*) ISrsNum 
        CLOSE(89)
* initial surface 
*hall
        OPoMin=[-11,-8,-8]
        OPoMax=[11,14,33]
*rock+waterpool
C        OPoMin=[-11,-8,-8]
C        OPoMax=[11,14,8]
*waterpool
C        OPoMin=[-8,-5,-5]
C        OPoMax=[8,11,5]
*AD
C        OPoMin=[-5.5,-2.5,-2.5]
C        OPoMax=[5.5,8.5,2.5]

        SVecN=0
        SLen=0
* 1st plane        
        SVecN(1,1) = 1
        SPoMin(1,1) = OPoMax(1)
        SPoMin(1,2) = OPoMin(2)
        SPoMin(1,3) = OPoMin(3)
        SLen(1,2) = OPoMax(2) - OPoMin(2)
        SLen(1,3) = OPoMax(3) - OPoMin(3)
* 2nd plane        
        SVecN(2,2) = 1
        SPoMin(2,1) = OPoMin(1)
        SPoMin(2,2) = OPoMax(2)
        SPoMin(2,3) = OPoMin(3)
        SLen(2,1) = OPoMax(1) - OPoMin(1)
        SLen(2,3) = OPoMax(3) - OPoMin(3)
* 3th plane        
        SVecN(3,1) = -1
        SPoMin(3,1) = OPoMin(1)
        SPoMin(3,2) = OPoMin(2)
        SPoMin(3,3) = OPoMin(3)
        SLen(3,2) = OPoMax(2) - OPoMin(2)
        SLen(3,3) = OPoMax(3) - OPoMin(3)
* 4th plane        
      SVecN(4,2) = -1
      SPoMin(4,1) = OPoMin(1)
      SPoMin(4,2) = OPoMin(2)
      SPoMin(4,3) = OPoMin(3)
      SLen(4,1) = OPoMax(1) - OPoMin(1)
      SLen(4,3) = OPoMax(3) - OPoMin(3)
* 5th plane        
        SVecN(5,3) = 1
        SPoMin(5,1) = OPoMin(1)
        SPoMin(5,2) = OPoMin(2)
        SPoMin(5,3) = OPoMax(3)
        SLen(5,1) = OPoMax(1) - OPoMin(1)
        SLen(5,2) = OPoMax(2) - OPoMin(2)

      END IF
*   
*  +-------------------------------------------------------------------*
*  Push one source particle to the stack. Note that you could as well
*  push many but this way we reserve a maximum amount of space in the
*  stack for the secondaries to be generated
* Npflka is the stack counter: of course any time source is called it
* must be =0
      NPFLKA = NPFLKA + 1
      if(ISrsNum.eq.0 .or. ISrsNum.gt.NLINES) then
          ISrsNum=1
      endif
C           IF(ISrsNum .LT. NextSeedNum+50) THEN
C               WRITE(*,*) ISrsNum,Enrgy(ISrsNum),
C     &Theta(ISrsNum),Phi(ISrsNum)
C           END IF
* Wt is the weight of the particle
      WTFLK  (NPFLKA) = 1 
      WEIPRI = WEIPRI + WTFLK (NPFLKA)
* Particle type (1=proton.....). Ijbeam is the type set by the BEAM
* card
*  fraction of muonPlus,m+
      DMPCoe=0.5652
      IONID = IJBEAM
      IF (FLRNDM(DUMMY) .LT. DMPCoe) THEN
          ILOFLK (NPFLKA) = 10 
      ELSE
          ILOFLK (NPFLKA) = 11 
      END IF
*  |  Flag this is prompt radiation
      LRADDC (NPFLKA) = .FALSE.
*  |
*  +-------------------------------------------------------------------*
* From this point .....
* Particle generation (1 for primaries)
      LOFLK  (NPFLKA) = 1
* User dependent flag:
      LOUSE  (NPFLKA) = 0
* User dependent spare variables:
      DO 100 ISPR = 1, MKBMX1
         SPAREK (ISPR,NPFLKA) = ZERZER
 100  CONTINUE
* User dependent spare flags:
      DO 200 ISPR = 1, MKBMX2
         ISPARK (ISPR,NPFLKA) = 0
 200  CONTINUE
* Save the track number of the stack particle:
      ISPARK (MKBMX2,NPFLKA) = NPFLKA
      NPARMA = NPARMA + 1
      NUMPAR (NPFLKA) = NPARMA
      NEVENT (NPFLKA) = 0
      DFNEAR (NPFLKA) = +ZERZER
* ... to this point: don't change anything
* Particle age (s)
      AGESTK (NPFLKA) = +ZERZER
      AKNSHR (NPFLKA) = -TWOTWO
* Group number for "low" energy neutrons, set to 0 anyway
      IGROUP (NPFLKA) = 0
* Kinetic energy of the particle (GeV)
      TKEFLK (NPFLKA) = Enrgy(ISrsNum)
* Particle momentum
      PMOFLK (NPFLKA) = SQRT ( TKEFLK (NPFLKA) * ( TKEFLK (NPFLKA)
     &                       + TWOTWO * AM (ILOFLK(NPFLKA)) ) )

*==
*  incident direction vector
      ProVec(1) = SIN (Theta(ISrsNum)/PIPIPI)*COS ( Phi(ISrsNum)/PIPIPI)
      ProVec(2) = SIN (Theta(ISrsNum)/PIPIPI)*SIN ( Phi(ISrsNum)/PIPIPI)
      ProVec(3) = -COS (Theta(ISrsNum)/PIPIPI)

*  total valid surface area
      TVaiS = 0
      SecTag = 0
      DO I = 1,MaxP
         TotS=1
         DO J=1,3
            IF ( SLen(I,J) .NE. 0 ) THEN
               DLenT=SLen(I,J) 
            ELSE
               DLenT=1
            END IF
            TotS = TotS*DLenT
         END DO
         ValidS(I) = DOT_PRODUCT(SVecN(I,1:3),ProVec)/
     &               SQRT(DOT_PRODUCT(SVecN(I,1:3),SVecN(I,1:3))*
     &               DOT_PRODUCT(ProVec,ProVec)) * (-TotS)
         IF (ValidS(I) .GT. 0) THEN
            SecTag(I) = 1 
            TVaiS = TVaiS + ValidS(I)
         END IF
      END DO
C      WRITE(*,*) 'TVaiS:' ,TVaiS
C      WRITE(*,*) 'ValidS:',(ValidS(I),I=1,MaxP)

*  uniform sampling 
      SR = FLRNDM(DUMMY)
      SRFlag = 0
      DO I = 1,MaxP
         IF ( SecTag(I) .EQ. 1 ) THEN
            SRFlag = SRFlag + ValidS(I)/TVaiS
            IF (SR .LT. SRFlag) THEN
*  find right surface
               PRVec(1)=FLRNDM(DUMMY)
               PRVec(2)=FLRNDM(DUMMY)
               PRVec(3)=FLRNDM(DUMMY)
*  !!! initial position
               DIniPo=((SPoMin(I,1:3)+PRVec*SLen(I,1:3))+
     &(-10000*ProVec))
C               WRITE(*,*) ISrsNum,'if initial position : ',
C     &                    (DIniPo(J),j=1,3)
               EXIT 
            END IF
         END IF 
      END DO
C      WRITE(*,*) ISrsNum,'initial position : ',(DIniPo(J),j=1,3)


* Cosines (tx,ty,tz)
      TXFLK  (NPFLKA) = ProVec(1)
      TYFLK  (NPFLKA) = ProVec(2)
      TZFLK  (NPFLKA) = ProVec(3)
C      TZFLK  (NPFLKA) = -SQRT ( ONEONE - TXFLK (NPFLKA)**2
C     &                       - TYFLK (NPFLKA)**2 ) !==ProVec(3)
* Particle coordinates
      XFLK   (NPFLKA) = DIniPo(1)
      YFLK   (NPFLKA) = DIniPo(2)
      ZFLK   (NPFLKA) = DIniPo(3)
*==

* Polarization cosines:
      TXPOL  (NPFLKA) = -TWOTWO
      TYPOL  (NPFLKA) = +ZERZER
      TZPOL  (NPFLKA) = +ZERZER
*  Calculate the total kinetic energy of the primaries: don't change
      IF ( ILOFLK (NPFLKA) .EQ. -2 .OR. ILOFLK (NPFLKA) .GT. 100000 )
     &   THEN
         TKESUM = TKESUM + TKEFLK (NPFLKA) * WTFLK (NPFLKA)
      ELSE IF ( ILOFLK (NPFLKA) .NE. 0 ) THEN
         TKESUM = TKESUM + ( TKEFLK (NPFLKA) + AMDISC (ILOFLK(NPFLKA)) )
     &          * WTFLK (NPFLKA)
      ELSE
         TKESUM = TKESUM + TKEFLK (NPFLKA) * WTFLK (NPFLKA)
      END IF
      RADDLY (NPFLKA) = ZERZER
*  Here we ask for the region number of the hitting point.
*     NREG (NPFLKA) = ...
*  The following line makes the starting region search much more
*  robust if particles are starting very close to a boundary:
      CALL GEOCRS ( TXFLK (NPFLKA), TYFLK (NPFLKA), TZFLK (NPFLKA) )
      CALL GEOREG ( XFLK  (NPFLKA), YFLK  (NPFLKA), ZFLK  (NPFLKA),
     &              NRGFLK(NPFLKA), IDISC )
*  Do not change these cards:
      CALL GEOHSM ( NHSPNT (NPFLKA), 1, -11, MLATTC )
      NLATTC (NPFLKA) = MLATTC
      CMPATH (NPFLKA) = ZERZER
      CALL SOEVSV
      ISrsNum=ISrsNum+1
      NextSeedNum=ISrsNum
      RETURN
*=== End of subroutine Source =========================================*
      END

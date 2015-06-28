*=== Source of muons at dayabay     
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
      DATA AFrac / 0 /
      DATA ANexFrac / 0 /
      DATA ISrsNum / 0 /
*
      PARAMETER(NLINES = 340000,MaxP=5)
      DIMENSION Enrgy(NLINES), PosX(NLINES), PosY(NLINES),PosZ(NLINES),
     &CosX(NLINES), CosY(NLINES),CosZ(NLINES)
      SAVE ISrsNum,LFIRST, Enrgy,PosX,PosY,PosZ,CosX,CosY,CosZ
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
     &ork/dayabay/neutronGen.DYB",STATUS="OLD")
        DO I = 1, NLINES
           READ(88,*) Enrgy(I),PosX(I),PosY(I),PosZ(I),
     &CosX(I),CosY(I),CosZ(I)
C      WRITE(*,*) Enrgy(I),PosX(I),PosY(I),PosZ(I),
C     &CosX(I),CosY(I),CosZ(I)
        END DO
        CLOSE(88)
        OPEN(UNIT=89,FILE="/afs/ihep.ac.cn/users/l/lidj/largedata/flukaW
     &ork/dayabay/NeuEAddFrac",STATUS="OLD")
           READ(89,*) AFrac 
        CLOSE(89)
        WRITE(*,*) "AFrac:",AFrac
        ANexFrac=AFrac+0.01
C        ANexFrac=AFrac + 1
C        ANexFrac=AFrac + 1./100
        OPEN(UNIT=99,FILE="/afs/ihep.ac.cn/users/l/lidj/largedata/flukaW
     &ork/dayabay/NeuEAddFrac",STATUS="REPLACE")
        WRITE(99,*) ANexFrac
        CLOSE(99)
        WRITE(*,*) "ANexFrac:",ANexFrac
      END IF
       ISrsNum = ISrsNum + 1
      Enrgy(1)=1
*  |
*  +-------------------------------------------------------------------*
*  Push one source particle to the stack. Note that you could as well
*  push many but this way we reserve a maximum amount of space in the
*  stack for the secondaries to be generated
*  Npflka is the stack counter: of course any time source is called it
*  must be =0
      NPFLKA = NPFLKA + 1
*  Wt is the weight of the particle
      WTFLK  (NPFLKA) = ONEONE
      WEIPRI = WEIPRI + WTFLK (NPFLKA)
*  Particle type (1=proton.....). Ijbeam is the type set by the BEAM
*  card
*  +-------------------------------------------------------------------*
*  |  (Radioactive) isotope:
      IF ( IJBEAM .EQ. -2 .AND. LRDBEA ) THEN
         IARES  = IPROA
         IZRES  = IPROZ
         IISRES = IPROM
         CALL STISBM ( IARES, IZRES, IISRES )
         IJHION = IPROZ  * 1000 + IPROA
         IJHION = IJHION * 100 + KXHEAV
         IONID  = IJHION
         CALL DCDION ( IONID )
         CALL SETION ( IONID )
*  |
*  +-------------------------------------------------------------------*
*  |  Heavy ion:
      ELSE IF ( IJBEAM .EQ. -2 ) THEN
         IJHION = IPROZ  * 1000 + IPROA
         IJHION = IJHION * 100 + KXHEAV
         IONID  = IJHION
         CALL DCDION ( IONID )
         CALL SETION ( IONID )
         ILOFLK (NPFLKA) = IJHION
*  |  Flag this is prompt radiation
         LRADDC (NPFLKA) = .FALSE.
*  |  Group number for "low" energy neutrons, set to 0 anyway
         IGROUP (NPFLKA) = 0
*  |
*  +-------------------------------------------------------------------*
*  |  Normal hadron:
      ELSE
         IONID = IJBEAM
         ILOFLK (NPFLKA) = IJBEAM
*  |  Flag this is prompt radiation
         LRADDC (NPFLKA) = .FALSE.
*  |  Group number for "low" energy neutrons, set to 0 anyway
         IGROUP (NPFLKA) = 0
      END IF
*  |
*  +-------------------------------------------------------------------*
*  From this point .....
*  Particle generation (1 for primaries)
      LOFLK  (NPFLKA) = 1
*  User dependent flag:
      LOUSE  (NPFLKA) = 0
*  No channeling:
      LCHFLK (NPFLKA) = .FALSE.
      DCHFLK (NPFLKA) = ZERZER
*  User dependent spare variables:
      DO 100 ISPR = 1, MKBMX1
         SPAREK (ISPR,NPFLKA) = ZERZER
 100  CONTINUE
*  User dependent spare flags:
      DO 200 ISPR = 1, MKBMX2
         ISPARK (ISPR,NPFLKA) = 0
 200  CONTINUE
*  Save the track number of the stack particle:
      ISPARK (MKBMX2,NPFLKA) = NPFLKA
      NPARMA = NPARMA + 1
      NUMPAR (NPFLKA) = NPARMA
      NEVENT (NPFLKA) = 0
      DFNEAR (NPFLKA) = +ZERZER
*  ... to this point: don't change anything
*  Particle age (s)
      AGESTK (NPFLKA) = +ZERZER
      AKNSHR (NPFLKA) = -TWOTWO

* Kinetic energy of the particle (GeV)

C      WRITE(*,*) "Enrgy(ISrsNum):",ISrsNum,Enrgy(ISrsNum)
      TKEFLK (NPFLKA) = Enrgy(ISrsNum)*AFrac
* Particle momentum
      PMOFLK (NPFLKA) = SQRT ( TKEFLK (NPFLKA) * ( TKEFLK (NPFLKA)
     &                       + TWOTWO * AM (IONID) ) )
* Cosines (tx,ty,tz)
      TXFLK  (NPFLKA) =CosX(ISrsNum) 
      TYFLK  (NPFLKA) =CosY(ISrsNum)
      TZFLK  (NPFLKA) =CosZ(ISrsNum)
C      TZFLK  (NPFLKA) = -SQRT ( ONEONE - TXFLK (NPFLKA)**2
C     &                       - TYFLK (NPFLKA)**2 ) !==ProVec(3)
* Particle coordinates
      XFLK   (NPFLKA) =PosX(ISrsNum)
      YFLK   (NPFLKA) =PosY(ISrsNum)
      ZFLK   (NPFLKA) =PosZ(ISrsNum)
*==
*  Polarization cosines:
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
      RETURN
*=== End of subroutine Source =========================================*
      END


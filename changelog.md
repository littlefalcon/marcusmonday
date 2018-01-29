### SNL41 29/1/18 2134
* change door blueprint to real door

### SNL39 25/1/18 0144
* rework inventory / add inventory slot ui

### SNL38 24/1/18 2303
* add inventory asset / bp

### SNL37 22/1/18 1810
* add all in game menu

### SNL36 23/1/18 0214
*  add all in game menu
	* bug at weapon selector

### SNL35 22/1/18 1810
* fix bug can shoot at main menu by change playercontroller

### SNL34 21/1/18 1629
* make mainmenu can load and pause exit to menu

### SNL33 21/1/18 1506
* main menu functionable
* bug can shoot at mainmenu
### SNL32 20/1/18 2115
* add health ammo max ammo user interface

### SNL30 18/1/18 2115
* add emitter class
* make bp_beam visual code to c++
* stop doing weapon system

### SNL29 15/1/18 1637
* move beam to c++
* error access again wtf and crash too
* done linetrace

### SNL28 15/1/18 1438
* beam weapon now can fire 
* fix by get parent(weapon) and get owner(of weapon) for access variable of BP_Beam

### SNL28 8/1/18 2015
* refactor FireMechacnicAuto
	* change variable name
	* delete some visual code in weapon bp
	* make hitscanfire method

### SNL27 8/1/18 1725
* fix childactor (BP_Semi) bug because of private member or no bpreadonly property

### SNL26 8/1/18 0153
* delete old semihitscan
* found BP Bug fix by reparent
### SNL25 7/1/18 1953
* make all visual in SEMI BP to c++ code
	* add linetracebysinglechannel to c++
	* add getcameralocation and forward  vector
	* fix crash when not hit actor

### SNL24 7/1/18 1534
* can't fix skeletal mesh bug so rework fire system next
### SNL23 5/1/18 1455
* refactor FireMechacnicAuto
	* change fire checker to hitscan or projectile (old is check semi or auto)
	* weapon can fire again bug because currentweapon check before get from character

### SNL22 5/1/18 1426
* refactor FireMechacnicAuto
	* move most code in tick to check weapon block
	* wip make weapon fire again
### SNL21 17/12/17 1726
* change bullet color
* add hitscan
* change weight of projectile
* BUG projectile bullet sway relative with gun need change to ref by crooshair
### SNL20 17/12/17 1440
* BP access bug stop do beam
### SNL19 16/12/17 2229
* add BP_Beam to bp_wp_beam 
* beam visual code complete
### SNL18 14/12/17 0120
* add inherit beam class in bp
### SNL17 13/12/17 1923
* FireMechanicAuto adapt use for semi
* refactor fire mechenic semi and autoS
### SNL16 12/12/17 0910
* Change Weapon
* make semi in auto class need to change
### SNL15 11/12/17 1810
* FIX -bug- bullet forwarding not sync with pitch(updown) 
* -bug- when camera near obstacle bullet spawn wrong area *because collision type
### SNL14 10/12/17 2323
* add spawn particle C++
* duplicate particle for dummy muzzleparticle
* #include "SpaceHorrorProjectile.h" at MasterWeapons.cpp
* spawn projectile bullet in MasterWeapon Class
* add rotation Yaw+90 for forward bullet
* bullet will freeze when not use bounce mechanic in ProjectileClass
* -bug- when camera near obstacle bullet spawn wrong area
* -bug- bullet forwarding not sync with pitch(updown) 

### SNL13 8/12/17 1605
* handle firing
	* add kismet gameplaystaticfor sound to master weapon class 
	* add sound to master class
* make skeletal mesh to inherit class at masterwapon class
* rename assemble dc_gun
* delete DC_Gun
* delete create gun function
* playsound when fire in BP now play in MasterWeapon class C++ 

### SNL12 8/12/17 1605
* delete weaponselector in BP
* try create new gun in bp_fpc // cancel
* use arm skeletal socket to connect gun to hand 

### SNL11 7/12/17 1630
* delete gun mesh at bp_wp_assemble for use gun in bp_fpc
* try create new gun in bp_fpc  

### SNL10 6/12/17 1614
* block fire when reloading
* attach gun to player 

### SNL9 6/12/17 1408
* add reload log
* fix method name
* add setammo method (inceaseammo(int amount)
* reload mechanic can regain ammo
### SNL8 6/12/17 1341
* Implement Reload Mechanic
* currentammo sync to magazinecapacity when begin play
### SNL7 6/12/17 1256
* Refactor FireAutomatic / MasterWeapon Class
### SNL6 6/12/17 1042
* fireMechanicauto now sync with firebutton
	* ammo decease when fire
	* firerate can control fire
### SNL5 30/11/17 1354
* BP_Beam and BP_FPC detach print sring
* can get acess variable from begin play not in constructor
* SpaceHorrorCharacter OnFire() StopFire() Method to Public

### SNL4 28/11/17 0315
* Now inherit class can communicate with parent class
### SNL3 27/11/17 2209
* Add FireMechacnicAuto class
	* Handle All Firing System
* Complete Test Commication between 2 class use DefaultSubObject and find class in BP with FNAME
### SNL2 26/11/17 1815
* Add Subclass (WeaponMechanic)
* Add Method in MasterWepon
* Add License to top of c++ files
### SNL1 26/11/17 1538
* Add Weapon Model and Muzzle Location to BP_WP_Assemnble 

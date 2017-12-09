### SNL13 8/12/17 1605
* handle firing
	* add kismet gameplaystaticfor sound to master weapon class 
	* add sound to master class
* make skeletal mesh to inherit class at masterwapon class
* rename assemble dc_gun
* delete DC_Gun
* delete create gun function

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

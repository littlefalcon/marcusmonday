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

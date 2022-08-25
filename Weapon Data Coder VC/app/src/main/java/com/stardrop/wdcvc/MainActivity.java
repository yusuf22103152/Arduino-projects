package com.stardrop.wdcvc;

import android.content.DialogInterface;
import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.WindowManager;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.SeekBar;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

import com.google.android.gms.ads.AdError;
import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.FullScreenContentCallback;
import com.google.android.gms.ads.LoadAdError;
import com.google.android.gms.ads.MobileAds;
import com.google.android.gms.ads.initialization.InitializationStatus;
import com.google.android.gms.ads.initialization.OnInitializationCompleteListener;
import com.google.android.gms.ads.interstitial.InterstitialAd;
import com.google.android.gms.ads.interstitial.InterstitialAdLoadCallback;

public class MainActivity extends AppCompatActivity {

    int fType_idx = 1,range_idx = 2, ammu_idx = 5, damage_idx = 6;
    String IDname,fTypeHolder,fType,range,ammu,damage;
    String output,filepath="Exported",filename="weapon.dat";

    TextView progRange,progAmmu,progDamage;

    private AdView mAdView;
    public InterstitialAd mInterstitialAd;

    boolean saved=false;

    ImageView IvWeapons,IvInfo;

    SeekBar sbRange,sbAmmu,sbDamage;
    Spinner spFType,spId,spFeature;
    Button Apply,Save,Export;

    String[] Unarmed = {"Unarmed","MELEE","2.4","250","100","1000","8","-1.0","0.6","-1.0","-1.0","0.1","0.65","0.30","unarmed","0","99","6","0","99","12","99","-1","-1","102000","0"};
    String[] BrassKnuckle = {"BrassKnuckle","MELEE","2.0","250","100","1000","16","-1.0","0.8","-1.0","-1.0","0.1","0.8","0.30","unarmed","5","20","14","3","17","11","99","259","-1","102000","0"};
    String[] ScrewDriver = {"ScrewDriver","MELEE","1.8","250","100","1000","45","-1.0","0.5","-1.0","-1.0","0.0","0.7","0.20","screwdrv","5","99","14","3","17","11","99","260","-1","115000","1"};
    String[] GolfClub = {"GolfClub","MELEE","1.5","250","100","1000","21","-1.0","0.8","-1.0","-1.0","0.1","0.8","0.30","golfclub","5","20","16","3","15","12","99","261","-1","102000","1"};
    String[] NightStick = {"NightStick","MELEE","1.5","250","100","1000","21","-1.0","0.8","-1.0","-1.0","0.1","0.8","0.30","baseball","5","20","14","3","17","11","99","262","-1","102000","1"};
    String[] Knife = {"Knife","MELEE","1.8","250","100","1000","21","-1.0","0.5","-1.0","-1.0","0.0","0.8","0.20","knife","5","99","14","3","17","11","99","263","-1","115000","1"};
    String[] BaseballBat = {"BaseballBat","MELEE","2.0","250","100","1000","21","-1.0","0.8","-1.0","-1.0","0.1","0.8","0.30","baseball","5","20","16","3","17","11","99","264","-1","102000","1"};
    String[] Hammer = {"Hammer","MELEE","1.5","250","100","1000","21","-1.0","0.8","-1.0","-1.0","0.1","0.8","0.30","baseball","5","20","14","3","17","11","99","265","-1","102000","1"};
    String[] Cleaver = {"Cleaver","MELEE","1.9","250","100","1000","24","-1.0","0.6","-1.0","-1.0","0.0","0.9","0.20","knife","5","99","14","3","17","11","99","266","-1","115000","1"};
    String[] Machete = {"Machete","MELEE","2.0","250","100","1000","24","-1.0","0.6","-1.0","-1.0","0.0","1.0","0.20","knife","5","99","14","3","17","11","99","267","-1","115000","1"};
    String[] Katana = {"Katana","MELEE","2.1","250","100","1000","30","-1.0","0.7","-1.0","-1.0","0.0","1.2","0.30","knife","5","99","14","3","17","11","99","268","-1","115000","1"};
    String[] Chainsaw = {"Chainsaw","MELEE","1.7","250","100","1000","35","-1.0","0.55","-1.0","-1.0","0.0","1.3","0.10","chainsaw","5","35","30","3","99","48","99","269","-1","102000","1"};

    String[] Grenade = {"Grenade","PROJECTILE","30.0","100","1","1","75","0.25","-1.0","800.0","1.0","0.0","0.0","0.0","grenade","0","99","10","0","99","6","99","270","-1","2424","2"};
    String[] DetonateGrenade = {"DetonateGrenade","PROJECTILE","30.0","100","1","1","75","0.25","-1.0","800.0","1.0","0.0","0.0","0.0","grenade","0","99","10","0","99","6","99","270","291","2424","2"};
    String[] TearGas = {"TearGas","PROJECTILE","30.0","100","1","1","75","0.25","-1.0","800.0","1.0","0.0","0.0","0.0","grenade","0","99","10","0","99","6","99","271","-1","2424","2"};
    String[] Molotov = {"Molotov","PROJECTILE","25.0","100","1","1","75","0.25","-1.0","2000.0","5.0","0.0","0.0","0.0","grenade","0","99","10","0","99","6","99","272","-1","2424","2"};
    String[] Rocket = {"Rocket","PROJECTILE","30.0","100","1","1","75","0.25","-1.0","800.0","1.0","0.0","0.0","0.0","unarmed","0","99","10","0","99","6","99","273","-1","2424","2"};
    String[] Colt45 = {"Colt45","INSTANT_HIT","30.0","250","450","17","25","-1.0","-1.0","-1.0","-1.0","0.30","0.0","0.09","colt45","11","18","14","11","18","12","99","274","-1","680C0","3"};
    String[] Python = {"Python","INSTANT_HIT","30.0","250","1000","6","135","-1.0","-1.0","-1.0","-1.0","0.41","0.03","0.12","python","10","31","14","14","37","16","40","275","-1","28040","3"};
    String[] Shotgun = {"Shotgun","INSTANT_HIT","40.0","250","450","1","80","-1.0","-1.0","-1.0","-1.0","0.86","-0.02","0.28","shotgun","12","34","15","9","26","13","30","277","-1","20040","4"};
    String[] Spas12Shotgun = {"Spas12Shotgun","INSTANT_HIT","30.0","250","750","7","100","-1.0","-1.0","-1.0","-1.0","0.85","-0.06","0.19","buddy","14","20","15","14","20","14","25","278","-1","20040","4"};
    String[] StubbyShotgun = {"StubbyShotgun","INSTANT_HIT","15.0","250","750","1","120","-1.0","-1.0","-1.0","-1.0","0.55","-0.02","0.13","buddy","14","50","15","14","56","15","25","279","-1","20040","4"};

    String[] Tec9 = {"Tec9","INSTANT_HIT","30.0","250","500","50","20","-1.0","-1.0","-1.0","-1.0","0.45","-0.05","0.11","colt45","11","15","14","11","15","12","99","281","-1","280C0","5"};
    String[] Uzi = {"Uzi","INSTANT_HIT","45.0","250","500","30","20","-1.0","-1.0","-1.0","-1.0","0.45","0.00","0.12","uzi","12","14","12","11","13","12","25","282","-1","28840","5"};
    String[] SilencedIngram = {"SilencedIngram","INSTANT_HIT","30.0","250","500","30","15","-1.0","-1.0","-1.0","-1.0","0.36","0.02","0.11","colt45","11","13","13","11","13","11","99","283","-1","280C0","5"};
    String[] Mp5 = {"Mp5","INSTANT_HIT","45.0","250","500","30","35","-1.0","-1.0","-1.0","-1.0","0.51","-0.01","0.20","uzi","11","14","11","11","14","12","30","284","-1","28840","5"};
    String[] m4 = {"m4","INSTANT_HIT","90.0","250","1000","30","40","-1.0","-1.0","-1.0","-1.0","0.88","-0.04","0.16","rifle","14","17","15","14","17","15","99","280","-1","28050","6"};
    String[] Ruger = {"Ruger","INSTANT_HIT","90.0","250","1000","30","35","-1.0","-1.0","-1.0","-1.0","1.00","-0.06","0.17","rifle","12","17","14","11","16","13","99","276","-1","28040","6"};
    String[] SniperRifle = {"SniperRifle","INSTANT_HIT","100.0","500","1401","1","125","-1.0","-1.0","-1.0","-1.0","0.0","0.66","0.05","unarmed","12","15","14","0","10","3","99","285","-1","100","8"};
    String[] LaserScope = {"LaserScope","INSTANT_HIT","100.0","150","1401","7","125","-1.0","-1.0","-1.0","-1.0","0.0","0.66","0.05","unarmed","2","8","3","0","10","3","99","286","-1","100","8"};

    String[] RocketLauncher = {"RocketLauncher","PROJECTILE","55.0","100","1200","1","75","2.0","-1.0","1000.0","1.0","0.42","0.0","0.05","unarmed","0","99","14","0","99","14","99","287","-1","324","7"};
    String[] FlameThrower = {"FlameThrower","AREA_EFFECT","5.1","100","100","500","25","0.65","0.075","1000.0","3.0","1.30","0.0","0.56","flame","12","13","12","6","7","7","25","288","-1","1E","7"};

    String[] M60 = {"M60","INSTANT_HIT","75.0","1","500","100","130","-1.0","-1.0","-1.0","-1.0","1.0","0.00","0.23","m60","12","16","13","10","12","10","30","289","-1","8040","7"};
    String[] Minigun = {"Minigun","INSTANT_HIT","75.0","1","350","500","140","-1.0","-1.0","-1.0","-1.0","1.28","0.00","0.50","flame","11","12","11","11","12","11","35","290","294","200","7"};

    String[] Detonator = {"Detonator","PROJECTILE","25.0","100","1","1","0","2.0","-1.0","2000.0","5.0","0.0","0.0","0.13","man","0","10","3","0","10","3","99","291","-1","200024","9"};
    String[] HeliCannon = {"HeliCannon","INSTANT_HIT","100.0","1","100","150","100","-1.0","-1.0","-1.0","-1.0","1.00","0.00","0.23","m60","12","16","13","10","14","12","30","289","-1","8040","7"};
    String[] Camera = {"Camera","CAMERA","100.0","500","1401","36","0","-1.0","-1.0","-1.0","-1.0","0.0","0.66","0.05","unarmed","0","10","3","0","10","3","25","292","-1","100","9"};

    void Initialize() {

        sbRange = findViewById(R.id.sb_range);
        sbRange.setMax(200);
        sbAmmu = findViewById(R.id.sb_ammu);
        sbAmmu.setMax(9999);
        sbDamage = findViewById(R.id.sb_damage);
        sbDamage.setMax(9999);

        progRange = findViewById(R.id.tv_progRange);
        progDamage = findViewById(R.id.tv_progDamage);
        progAmmu = findViewById(R.id.tv_progAmmu);

        IvInfo = findViewById(R.id.iv_informations);
        IvWeapons = findViewById(R.id.iv_weapons);

        spId = findViewById(R.id.sp_id);
        spFType = findViewById(R.id.sp_fireType);
        spFeature = findViewById(R.id.sp_feature);

        Apply = findViewById(R.id.bt_apply);
        Save = findViewById(R.id.bt_save);
        Export = findViewById(R.id.bt_export);

        ArrayAdapter<String> AdaptId = new ArrayAdapter<String>(MainActivity.this, android.R.layout.simple_list_item_1,getResources().getStringArray(R.array.name));
        ArrayAdapter<String> AdaptFType = new ArrayAdapter<String>(MainActivity.this, android.R.layout.simple_list_item_1,getResources().getStringArray(R.array.fireType));
        ArrayAdapter<String> AdaptFeature = new ArrayAdapter<String>(MainActivity.this, android.R.layout.simple_list_item_1,getResources().getStringArray(R.array.feature));


        AdaptFType.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        AdaptId.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        AdaptFeature.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);

        spId.setAdapter(AdaptId);
        spFType.setAdapter(AdaptFType);
        spFeature.setAdapter(AdaptFeature);


    }



    public void cOfType(View view) {
        Toast.makeText(this, "Fire type : Select firing type among these options", Toast.LENGTH_SHORT).show();
    }
    public void cOfRange(View view) {
        Toast.makeText(this, "Range : The range of the bullet in units", Toast.LENGTH_SHORT).show();
    }
    public void cOAAmmu(View view) {
        Toast.makeText(this, "Amount of ammunition : The number of ammo per clip. Or you can say the number of ammunition it will fire before each reload. So the more is better", Toast.LENGTH_SHORT).show();
    }
    public void cODamage(View view) {
        Toast.makeText(this, "Damage : Damage done to damageable objects; damage done to characters are within the range of the value while to others are accurate to the value", Toast.LENGTH_SHORT).show();
    }


    @Override
    public void onBackPressed() {
        AlertDialog backPress = new AlertDialog.Builder(MainActivity.this).setTitle("Exit?").setMessage("Are you sure you want to exit?")
                .setPositiveButton("Exit", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        finish();
                    }
                }).setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {

                    }
                }).create();
        backPress.show();
    }

    void showInters() {
        if (mInterstitialAd!=null) {
            mInterstitialAd.show(MainActivity.this);
        }
    }

    void setPropertiesTo(String[] weaponArray) {
        weaponArray[fType_idx] = fType;
        weaponArray[range_idx] = range;
        weaponArray[ammu_idx] = ammu;
        weaponArray[damage_idx] = damage;
    }


    void collect() {
        fTypeHolder = spFType.getSelectedItem().toString();
        switch (fTypeHolder) {
            case "Melee":
                fType = "MELEE";
                break;
            case "Projectile":
                fType = "PROJECTILE";
                break;
            case "Instant hit":
                fType = "INSTANT_HIT ";
                break;
            case "Area effect":
                fType = "AREA_EFFECT";
                break;
        }

        range = String.valueOf(sbRange.getProgress());
        ammu = String.valueOf(sbAmmu.getProgress());
        damage = String.valueOf(sbDamage.getProgress());
    }


    void save () {
        IDname = spId.getSelectedItem().toString();
        switch (IDname) {
            case "Unarmed":
                setPropertiesTo(Unarmed);

                break;
            case "Brass knuckle":
                setPropertiesTo(BrassKnuckle);
                break;
            case "Screw driver":
                setPropertiesTo(ScrewDriver);
                break;
            case "Golf stick":
                setPropertiesTo(GolfClub);
                break;
            case "Night stick":
                setPropertiesTo(NightStick);
                break;
            case "Knife":
                setPropertiesTo(Knife);
                break;
            case "Baseball bat":
                setPropertiesTo(BaseballBat);
                break;
            case "Hammer":
                setPropertiesTo(Hammer);
                break;
            case "Cleaver":
                setPropertiesTo(Cleaver);
                break;
            case "Machete":
                setPropertiesTo(Machete);
                break;
            case "Katana":
                setPropertiesTo(Katana);
                break;
            case "Chainsaw":
                setPropertiesTo(Chainsaw);
                break;
            case "Grenade":
                setPropertiesTo(Grenade);
                break;
            case "Detonate grenade":
                setPropertiesTo(DetonateGrenade);
                break;
            case "Tear gas":
                setPropertiesTo(TearGas);
                break;
            case "Molotov":
                setPropertiesTo(Molotov);
                break;
            case "Colt45":
                setPropertiesTo(Colt45);
                break;
            case "Python":
                setPropertiesTo(Python);
                break;
            case "Shotgun":
                setPropertiesTo(Shotgun);
                break;
            case "Spas 12 Shotgun":
                setPropertiesTo(Spas12Shotgun);
                break;
            case "Stubby Shotgun":
                setPropertiesTo(StubbyShotgun);
                break;
            case "Tec9":
                setPropertiesTo(Tec9);
                break;
            case "Uzi":
                setPropertiesTo(Uzi);
                break;
            case "Silenced Ingram":
                setPropertiesTo(SilencedIngram);
                break;
            case "Mp5":
                setPropertiesTo(Mp5);
                break;
            case "M4":
                setPropertiesTo(m4);
                break;
            case "Ruger":
                setPropertiesTo(Ruger);
                break;
            case "Sniper rifle":
                setPropertiesTo(SniperRifle);
                break;
            case "Rocket launcher":
                setPropertiesTo(RocketLauncher);
                break;
            case "Flame thrower":
                setPropertiesTo(FlameThrower);
                break;
            case "M60":
                setPropertiesTo(M60);
                break;
            case "Minigun":
                setPropertiesTo(Minigun);
                break;
            case "Heli canon":
                setPropertiesTo(HeliCannon);
                break;
        }
        Toast.makeText(this, IDname+ " properties has successfully been saved", Toast.LENGTH_SHORT).show();

    }

    @RequiresApi(api = Build.VERSION_CODES.O)
    void export() {
        showInters();
        output = String.join(" ",Unarmed)+
                "\n"+String.join(" ",BrassKnuckle) +
                "\n"+String.join(" ",ScrewDriver) +
                "\n"+String.join(" ",GolfClub) +
                "\n"+String.join(" ",NightStick) +
                "\n"+String.join(" ",Knife) +
                "\n"+String.join(" ",BaseballBat) +
                "\n"+String.join(" ",Hammer) +
                "\n"+String.join(" ",Cleaver) +
                "\n"+String.join(" ",Machete) +
                "\n"+String.join(" ",Katana) +
                "\n"+String.join(" ",Chainsaw) +
                "\n"+String.join(" ",Grenade) +
                "\n"+String.join(" ",DetonateGrenade) +
                "\n"+String.join(" ",TearGas) +
                "\n"+String.join(" ",Molotov) +
                "\n"+String.join(" ",Rocket) +
                "\n"+String.join(" ",Colt45) +
                "\n"+String.join(" ",Python) +
                "\n"+String.join(" ",Shotgun) +
                "\n"+String.join(" ",Spas12Shotgun) +
                "\n"+String.join(" ",StubbyShotgun) +
                "\n"+String.join(" ",Tec9) +
                "\n"+String.join(" ",Uzi) +
                "\n"+String.join(" ",SilencedIngram) +
                "\n"+String.join(" ",Mp5) +
                "\n"+String.join(" ",m4) +
                "\n"+String.join(" ",Ruger) +
                "\n"+String.join(" ",SniperRifle) +
                "\n"+String.join(" ",LaserScope) +
                "\n"+String.join(" ",RocketLauncher) +
                "\n"+String.join(" ",FlameThrower) +
                "\n"+String.join(" ",M60) +
                "\n"+String.join(" ",Minigun) +
                "\n"+String.join(" ",Detonator) +
                "\n"+String.join(" ",HeliCannon) +
                "\n"+String.join(" ",Camera) +
                "\nENDWEAPONDATA";

        File myExternalFiles = new File(getExternalFilesDir(filepath),filename);
        FileOutputStream fos = null;
        try {
            fos = new FileOutputStream(myExternalFiles);
            fos.write(output.getBytes());
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        AlertDialog exportedAlert = new AlertDialog.Builder(MainActivity.this).setTitle("Exported").setMessage("File named \"weapon.dat\" has successfully been exported to Android/data/com.stardrop.wdcvc/files/Exported/ \nIf you dont know how to install then click on info button and there will be a link given of a tutorial")
                .setPositiveButton("Ok", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                    }
                }).create();
        exportedAlert.show();
    }

    private void getProgress(String rangeVar,String ammuVar,String damVar) {
        sbRange.setProgress((int) Float.parseFloat(rangeVar));
        sbAmmu.setProgress((int) Float.parseFloat(ammuVar));
        sbDamage.setProgress((int) Float.parseFloat(damVar));
    }


    void onWeaponSelect() {
        switch (spId.getSelectedItem().toString()) {
            case "Unarmed" : {
                IvWeapons.setImageResource(R.drawable.unarmed);
                spFType.setSelection(0);
                getProgress(Unarmed[range_idx],Unarmed[ammu_idx],Unarmed[damage_idx]);
                break;
            }
            case "Brass knuckle" : {
                IvWeapons.setImageResource(R.drawable.brass_knuckle);
                spFType.setSelection(0);
                getProgress(BrassKnuckle[range_idx],BrassKnuckle[ammu_idx],BrassKnuckle[damage_idx]);
                break;
            }
            case "Screw driver" : {
                IvWeapons.setImageResource(R.drawable.screw_driver);
                spFType.setSelection(0);
                getProgress(ScrewDriver[range_idx],ScrewDriver[ammu_idx],ScrewDriver[damage_idx]);
                break;
            }
            case "Golf stick" : {
                IvWeapons.setImageResource(R.drawable.golf_stick);
                spFType.setSelection(0);
                getProgress(GolfClub[range_idx],GolfClub[ammu_idx],GolfClub[damage_idx]);
                break;
            }
            case "Night stick" : {
                IvWeapons.setImageResource(R.drawable.night_stick);
                spFType.setSelection(0);
                getProgress(NightStick[range_idx],NightStick[ammu_idx],NightStick[damage_idx]);
                break;
            }
            case "Knife" : {
                IvWeapons.setImageResource(R.drawable.knife);
                spFType.setSelection(0);
                getProgress(Knife[range_idx],Knife[ammu_idx],Knife[damage_idx]);
                break;
            }
            case "Baseball bat" : {
                IvWeapons.setImageResource(R.drawable.baseball_bat);
                spFType.setSelection(0);
                getProgress(BaseballBat[range_idx],BaseballBat[ammu_idx],BaseballBat[damage_idx]);
                break;
            }
            case "Hammer" : {
                IvWeapons.setImageResource(R.drawable.hammer);
                spFType.setSelection(0);
                getProgress(Hammer[range_idx],Hammer[ammu_idx],Hammer[damage_idx]);
                break;
            }
            case "Cleaver" : {
                IvWeapons.setImageResource(R.drawable.cleaver);
                spFType.setSelection(0);
                getProgress(Cleaver[range_idx],Cleaver[ammu_idx],Cleaver[damage_idx]);
                break;
            }
            case "Machete" : {
                IvWeapons.setImageResource(R.drawable.machete);
                spFType.setSelection(0);
                getProgress(Machete[range_idx],Machete[ammu_idx],Machete[damage_idx]);
                break;
            }
            case "Katana" : {
                IvWeapons.setImageResource(R.drawable.katana);
                spFType.setSelection(0);
                getProgress(Katana[range_idx],Katana[ammu_idx],Katana[damage_idx]);
                break;
            }
            case "Chainsaw" : {
                IvWeapons.setImageResource(R.drawable.sawgun);
                spFType.setSelection(0);
                getProgress(Chainsaw[range_idx],Chainsaw[ammu_idx],Chainsaw[damage_idx]);
                break;
            }
            case "Grenade" : {
                IvWeapons.setImageResource(R.drawable.grenade);
                spFType.setSelection(1);
                getProgress(Grenade[range_idx],Grenade[ammu_idx],Grenade[damage_idx]);
                break;
            }
            case "Detonate grenade" : {
                IvWeapons.setImageResource(R.drawable.detonate_grenade);
                spFType.setSelection(1);
                getProgress(DetonateGrenade[range_idx],DetonateGrenade[ammu_idx],DetonateGrenade[damage_idx]);
                break;
            }
            case "Tear gas" : {
                IvWeapons.setImageResource(R.drawable.tear_gas);
                spFType.setSelection(1);
                getProgress(TearGas[range_idx],TearGas[ammu_idx],TearGas[damage_idx]);
                break;
            }
            case "Molotov" : {
                IvWeapons.setImageResource(R.drawable.molotov);
                spFType.setSelection(1);
                getProgress(Molotov[range_idx],Molotov[ammu_idx],Molotov[damage_idx]);
                break;
            }
            case "Colt45" : {
                IvWeapons.setImageResource(R.drawable.colt45);
                spFType.setSelection(2);
                getProgress(Colt45[range_idx],Colt45[ammu_idx],Colt45[damage_idx]);
                break;
            }
            case "Python" : {
                IvWeapons.setImageResource(R.drawable.python);
                spFType.setSelection(2);
                getProgress(Python[range_idx],Python[ammu_idx],Python[damage_idx]);
                break;
            }
            case "Shotgun" : {
                IvWeapons.setImageResource(R.drawable.shotgun);
                spFType.setSelection(2);
                getProgress(Shotgun[range_idx],Shotgun[ammu_idx],Shotgun[damage_idx]);
                break;
            }
            case "Spas 12 Shotgun" : {
                IvWeapons.setImageResource(R.drawable.spas_12_shotgun);
                spFType.setSelection(2);
                getProgress(Spas12Shotgun[range_idx],Spas12Shotgun[ammu_idx],Spas12Shotgun[damage_idx]);
                break;
            }
            case "Stubby Shotgun" : {
                IvWeapons.setImageResource(R.drawable.stubby_shotgun);
                spFType.setSelection(2);
                getProgress(StubbyShotgun[range_idx],StubbyShotgun[ammu_idx],StubbyShotgun[damage_idx]);
                break;
            }
            case "Tec9" : {
                IvWeapons.setImageResource(R.drawable.tec9);
                spFType.setSelection(2);
                getProgress(Tec9[range_idx],Tec9[ammu_idx],Tec9[damage_idx]);
                break;
            }
            case "Uzi" : {
                IvWeapons.setImageResource(R.drawable.uzi);
                spFType.setSelection(2);
                getProgress(Uzi[range_idx],Uzi[ammu_idx],Uzi[damage_idx]);
                break;
            }
            case "Silenced Ingram" : {
                IvWeapons.setImageResource(R.drawable.silenced_ingram);
                spFType.setSelection(2);
                getProgress(SilencedIngram[range_idx],SilencedIngram[ammu_idx],SilencedIngram[damage_idx]);
                break;
            }
            case "Mp5" : {
                IvWeapons.setImageResource(R.drawable.mp5);
                spFType.setSelection(2);
                getProgress(Mp5[range_idx],Mp5[ammu_idx],Mp5[damage_idx]);
                break;
            }
            case "M4" : {
                IvWeapons.setImageResource(R.drawable.m4);
                spFType.setSelection(2);
                getProgress(m4[range_idx],m4[ammu_idx],m4[damage_idx]);
                break;
            }
            case "Ruger" : {
                IvWeapons.setImageResource(R.drawable.ruger);
                spFType.setSelection(2);
                getProgress(Ruger[range_idx],Ruger[ammu_idx],Ruger[damage_idx]);
                break;
            }
            case "Sniper rifle" : {
                IvWeapons.setImageResource(R.drawable.sniper_rifle);
                spFType.setSelection(2);
                getProgress(SniperRifle[range_idx],SniperRifle[ammu_idx],SniperRifle[damage_idx]);
                break;
            }
            case "Rocket launcher" : {
                IvWeapons.setImageResource(R.drawable.rocket_launcher);
                spFType.setSelection(1);
                getProgress(RocketLauncher[range_idx],RocketLauncher[ammu_idx],RocketLauncher[damage_idx]);
                break;
            }
            case "Flame thrower" : {
                IvWeapons.setImageResource(R.drawable.flame_thrower);
                spFType.setSelection(3);
                getProgress(FlameThrower[range_idx],FlameThrower[ammu_idx],FlameThrower[damage_idx]);
                break;
            }
            case "M60" : {
                IvWeapons.setImageResource(R.drawable.m60);
                spFType.setSelection(2);
                getProgress(M60[range_idx],M60[ammu_idx],M60[damage_idx]);
                break;
            }
            case "Minigun" : {
                IvWeapons.setImageResource(R.drawable.minigun);
                spFType.setSelection(2);
                getProgress(Minigun[range_idx],Minigun[ammu_idx],Minigun[damage_idx]);
                break;
            }
            case "Heli canon" : {
                IvWeapons.setImageResource(R.drawable.heli_canon);
                spFType.setSelection(2);
                getProgress(HeliCannon[range_idx],HeliCannon[ammu_idx],HeliCannon[damage_idx]);
                break;
            }

        }
    }


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,WindowManager.LayoutParams.FLAG_FULLSCREEN);

        MobileAds.initialize(this, new OnInitializationCompleteListener() {
            @Override
            public void onInitializationComplete(InitializationStatus initializationStatus) {
            }
        });

        Initialize();

        Apply.setOnClickListener(new View.OnClickListener() {
            @RequiresApi(api = Build.VERSION_CODES.O)
            @Override
            public void onClick(View v) {
                saved = false;
                switch (spFeature.getSelectedItem().toString()) {
                    case "Extreme":
                        sbRange.setProgress(sbRange.getMax());
                        sbAmmu.setProgress(sbAmmu.getMax());
                        sbDamage.setProgress(sbDamage.getMax());
                        break;
                    case "Inability":
                        sbRange.setProgress(sbRange.getMin());
                        sbAmmu.setProgress(sbAmmu.getMin());
                        sbDamage.setProgress(sbDamage.getMin());
                        break;
                }
                Toast.makeText(MainActivity.this, "Special feature applied. Keep them unchanged and save to get full effect", Toast.LENGTH_SHORT).show();
            }
        });

        sbRange.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                saved = false;
                progRange.setText(String.valueOf(progress));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
        sbAmmu.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                saved = false;
                progAmmu.setText(String.valueOf(progress));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
        sbDamage.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                saved = false;
                progDamage.setText(String.valueOf(progress));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

        Save.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                saved=true;
                collect();
                save();
            }
        });

        spId.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                saved=false;
                onWeaponSelect();
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {

            }
        });

        Export.setOnClickListener(new View.OnClickListener() {
            @RequiresApi(api = Build.VERSION_CODES.O)
            @Override
            public void onClick(View v) {
                if (!saved) {
                    AlertDialog saveAlert = new AlertDialog.Builder(MainActivity.this).setTitle("Warning").setMessage("You didn't save your last edit. Are you sure you want to export?")
                            .setPositiveButton("Yes", new DialogInterface.OnClickListener() {
                                @Override
                                public void onClick(DialogInterface dialog, int which) {
                                    export();
                                }
                            }).setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
                                @Override
                                public void onClick(DialogInterface dialog, int which) {

                                }
                            }).create();
                    saveAlert.show();
                } else {
                    export();
                }

            }
        });

        IvInfo.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent infoIntent = new Intent(MainActivity.this,InfoActivity.class);
                startActivity(infoIntent);
            }
        });

        //Banner Ad unit

        mAdView = findViewById(R.id.adView);
        AdRequest adRequest = new AdRequest.Builder().build();
        mAdView.loadAd(adRequest);

        mAdView.setAdListener(new AdListener() {
            @Override
            public void onAdLoaded() {
                // Code to be executed when an ad finishes loading.
                super.onAdLoaded();
            }

            @Override
            public void onAdFailedToLoad(LoadAdError adError) {
                // Code to be executed when an ad request fails.
                super.onAdFailedToLoad(adError);
                mAdView.loadAd(adRequest);
            }

            @Override
            public void onAdOpened() {
                // Code to be executed when an ad opens an overlay that
                // covers the screen.
            }

            @Override
            public void onAdClicked() {
                // Code to be executed when the user clicks on an ad.
            }

            @Override
            public void onAdClosed() {
                // Code to be executed when the user is about to return
                // to the app after tapping on an ad.
            }
        });

        //Interstitial ad unit

        AdRequest adRequestInst = new AdRequest.Builder().build();

        InterstitialAd.load(this,getString(R.string.inst_adId), adRequestInst, new InterstitialAdLoadCallback() {
            @Override
            public void onAdLoaded(@NonNull InterstitialAd interstitialAd) {
                // The mInterstitialAd reference will be null until
                // an ad is loaded.
                mInterstitialAd = interstitialAd;
            }

            @Override
            public void onAdFailedToLoad(@NonNull LoadAdError loadAdError) {
                // Handle the error
                mInterstitialAd = null;
            }
        });







    }
}
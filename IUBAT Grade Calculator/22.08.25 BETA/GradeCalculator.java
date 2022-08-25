package com.stardrop.iubatpe;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.Spinner;
import android.widget.TextView;
import java.util.Objects;

//Task left : Add signature code


public class GradeCalculator extends AppCompatActivity {

    LinearLayout loutSub1,loutSub2,loutSub3,loutSub4,loutSub5,loutSub6;
    LinearLayout loutSem1,loutSem2,loutSem3,loutSem4,loutSem5,loutSem6,loutSem7,loutSem8,loutSem9,loutSem10,loutSem11,loutSem12;
    Button btAdd,btCalcSGPA,btCalcCGPA,btRefresh,btHideMsg,btAuthor;

    TextView tvPnt1,tvPnt2,tvPnt3,tvPnt4,tvPnt5,tvPnt6,tvMsg;
    EditText etSub1,etSub2,etSub3,etSub4,etSub5,etSub6;
    EditText etSem1,etSem2,etSem3,etSem4,etSem5,etSem6,etSem7,etSem8,etSem9,etSem10,etSem11,etSem12;

    Spinner spCrh1,spCrh2,spCrh3,spCrh4,spCrh5,spCrh6;
    Spinner spCrhSem1,spCrhSem2,spCrhSem3,spCrhSem4,spCrhSem5,spCrhSem6,spCrhSem7,spCrhSem8,spCrhSem9,spCrhSem10,spCrhSem11,spCrhSem12;
    Spinner spGrd1,spGrd2,spGrd3,spGrd4,spGrd5,spGrd6;
    LinearLayout loutSGPA,loutSGPAheader,loutCGPA,loutCGPAheader,loutWindow;
    int loutsSGPAvisible=2,loutsCGPAvisible=2;

    boolean sgpaMode=true;

    double sgpa=0.0;
    double cgpa=0.0;

    Handler handleWindow=new Handler();

    final int s1=0,s2=1,s3=2,s4=3,s5=4,s6=5;
    final int A4=0,Bpos37=1,B34=2,Bneg31=3,Cpos28=4,C25=5,Cneg22=6,Dpos15=7,D1=8,F0=9;
    String[] letterGrades ={"F","F","F","F","F","F"};
    double[] pointSGPA = {0,0,0,0,0,0};
    double[] pointCGPA = {0,0,0,0,0,0,0,0,0,0,0,0};
    int[] crHoursSGPA ={0,0,0,0,0,0};
    int[] crHoursCGPA ={0,0,0,0,0,0,0,0,0,0,0,0};

    void initialize() {
        //Layouts
        btAuthor=findViewById(R.id.bt_Author);

        loutSub1=findViewById(R.id.lout_sub1);
        loutSub2=findViewById(R.id.lout_sub2);
        loutSub3=findViewById(R.id.lout_sub3);
        loutSub4=findViewById(R.id.lout_sub4);
        loutSub5=findViewById(R.id.lout_sub5);
        loutSub6=findViewById(R.id.lout_sub6);

        loutSem1=findViewById(R.id.lout_sem1);
        loutSem2=findViewById(R.id.lout_sem2);
        loutSem3=findViewById(R.id.lout_sem3);
        loutSem4=findViewById(R.id.lout_sem4);
        loutSem5=findViewById(R.id.lout_sem5);
        loutSem6=findViewById(R.id.lout_sem6);
        loutSem7=findViewById(R.id.lout_sem7);
        loutSem8=findViewById(R.id.lout_sem8);
        loutSem9=findViewById(R.id.lout_sem9);
        loutSem10=findViewById(R.id.lout_sem10);
        loutSem11=findViewById(R.id.lout_sem11);
        loutSem12=findViewById(R.id.lout_sem12);


        loutSGPA=findViewById(R.id.lout_sgpa);
        loutCGPA=findViewById(R.id.lout_cgpa);

        loutSGPAheader=findViewById(R.id.lout_sgpaHeaders);
        loutCGPAheader=findViewById(R.id.lout_cgpaHeaders);

        loutWindow=findViewById(R.id.lout_window);

        //Buttons
        btAdd=findViewById(R.id.bt_add);
        btCalcSGPA=findViewById(R.id.bt_CalcSGPA);
        btCalcCGPA=findViewById(R.id.bt_CalcCGPA);
        btRefresh=findViewById(R.id.bt_refresh);
        btHideMsg=findViewById(R.id.bt_hideMsg);

        //Text views
        tvPnt1=findViewById(R.id.tv_pntSub1);
        tvPnt2=findViewById(R.id.tv_pntSub2);
        tvPnt3=findViewById(R.id.tv_pntSub3);
        tvPnt4=findViewById(R.id.tv_pntSub4);
        tvPnt5=findViewById(R.id.tv_pntSub5);
        tvPnt6=findViewById(R.id.tv_pntSub6);

        tvMsg=findViewById(R.id.tv_message);

        //Edit texts
        etSub1=findViewById(R.id.et_sub1);
        etSub2=findViewById(R.id.et_sub2);
        etSub3=findViewById(R.id.et_sub3);
        etSub4=findViewById(R.id.et_sub4);
        etSub5=findViewById(R.id.et_sub5);
        etSub6=findViewById(R.id.et_sub6);

        etSem1=findViewById(R.id.et_sgpaSem1);
        etSem2=findViewById(R.id.et_sgpaSem2);
        etSem3=findViewById(R.id.et_sgpaSem3);
        etSem4=findViewById(R.id.et_sgpaSem4);
        etSem5=findViewById(R.id.et_sgpaSem5);
        etSem6=findViewById(R.id.et_sgpaSem6);
        etSem7=findViewById(R.id.et_sgpaSem7);
        etSem8=findViewById(R.id.et_sgpaSem8);
        etSem9=findViewById(R.id.et_sgpaSem9);
        etSem10=findViewById(R.id.et_sgpaSem10);
        etSem11=findViewById(R.id.et_sgpaSem11);
        etSem12=findViewById(R.id.et_sgpaSem12);

        //Spinners
        spCrh1=findViewById(R.id.sp_crh1);
        spCrh2=findViewById(R.id.sp_crh2);
        spCrh3=findViewById(R.id.sp_crh3);
        spCrh4=findViewById(R.id.sp_crh4);
        spCrh5=findViewById(R.id.sp_crh5);
        spCrh6=findViewById(R.id.sp_crh6);

        spGrd1=findViewById(R.id.sp_grd1);
        spGrd2=findViewById(R.id.sp_grd2);
        spGrd3=findViewById(R.id.sp_grd3);
        spGrd4=findViewById(R.id.sp_grd4);
        spGrd5=findViewById(R.id.sp_grd5);
        spGrd6=findViewById(R.id.sp_grd6);

        spCrhSem1=findViewById(R.id.sp_crhSem1);
        spCrhSem2=findViewById(R.id.sp_crhSem2);
        spCrhSem3=findViewById(R.id.sp_crhSem3);
        spCrhSem4=findViewById(R.id.sp_crhSem4);
        spCrhSem5=findViewById(R.id.sp_crhSem5);
        spCrhSem6=findViewById(R.id.sp_crhSem6);
        spCrhSem7=findViewById(R.id.sp_crhSem7);
        spCrhSem8=findViewById(R.id.sp_crhSem8);
        spCrhSem9=findViewById(R.id.sp_crhSem9);
        spCrhSem10=findViewById(R.id.sp_crhSem10);
        spCrhSem11=findViewById(R.id.sp_crhSem11);
        spCrhSem12=findViewById(R.id.sp_crhSem12);

        //Adapters
        ArrayAdapter<String> AdaptCrHours = new ArrayAdapter<String>(GradeCalculator.this, android.R.layout.simple_list_item_1,getResources().getStringArray(R.array.crHours));
        AdaptCrHours.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);

        ArrayAdapter<String> AdaptGrades = new ArrayAdapter<String>(GradeCalculator.this, android.R.layout.simple_list_item_1,getResources().getStringArray(R.array.Grades));
        AdaptGrades.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);

        ArrayAdapter<String> AdaptCrHoursTotal = new ArrayAdapter<>(GradeCalculator.this, android.R.layout.simple_list_item_1,getResources().getStringArray(R.array.crHoursTotal));
        AdaptGrades.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);

        spCrh1.setAdapter(AdaptCrHours);
        spCrh2.setAdapter(AdaptCrHours);
        spCrh3.setAdapter(AdaptCrHours);
        spCrh4.setAdapter(AdaptCrHours);
        spCrh5.setAdapter(AdaptCrHours);
        spCrh6.setAdapter(AdaptCrHours);

        spGrd1.setAdapter(AdaptGrades);
        spGrd2.setAdapter(AdaptGrades);
        spGrd3.setAdapter(AdaptGrades);
        spGrd4.setAdapter(AdaptGrades);
        spGrd5.setAdapter(AdaptGrades);
        spGrd6.setAdapter(AdaptGrades);

        spCrhSem1.setAdapter(AdaptCrHoursTotal);
        spCrhSem2.setAdapter(AdaptCrHoursTotal);
        spCrhSem3.setAdapter(AdaptCrHoursTotal);
        spCrhSem4.setAdapter(AdaptCrHoursTotal);
        spCrhSem5.setAdapter(AdaptCrHoursTotal);
        spCrhSem6.setAdapter(AdaptCrHoursTotal);
        spCrhSem7.setAdapter(AdaptCrHoursTotal);
        spCrhSem8.setAdapter(AdaptCrHoursTotal);
        spCrhSem9.setAdapter(AdaptCrHoursTotal);
        spCrhSem10.setAdapter(AdaptCrHoursTotal);
        spCrhSem11.setAdapter(AdaptCrHoursTotal);
        spCrhSem12.setAdapter(AdaptCrHoursTotal);

    }

    private final Runnable runHideWindow=new Runnable() {
        @Override
        public void run() {
            loutWindow.setVisibility(View.INVISIBLE);
        }
    };
    boolean cHoursArent0() {
        int notNull=0;
        if (sgpaMode) {
            for(int i=0;i<6;i++) {
                if(crHoursSGPA[i]!=0) {
                    notNull++;
                }
            }
        }
        else {
            for(int i=0;i<12;i++) {
                if(crHoursCGPA[i]!=0) {
                    notNull++;
                }
            }

        }
        return notNull>=2;
    }

    String status(int point) {
        String res="";
        switch (point) {
            case 4:
                res= "Excellent";
                break;
            case 3:
                res= "Good";
                break;
            case 2:
                res= "Fair";
                break;
            case 1:
                res= "Passing";
                break;
            case 0:
                res= "Failing";
                break;

        }
        return res;
    }

    void setCrHours(Spinner sp,int serial) {
        sp.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {

                int crH=Integer.parseInt(sp.getSelectedItem().toString());

                if(sgpaMode) {
                    crHoursSGPA[serial]=crH;
                }
                else {
                    crHoursCGPA[serial]=crH;
                }

            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {

            }
        });
    }

    void cgpaInputManage(EditText cgpaInp,int serial) {
        cgpaInp.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {

            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {

                String gotText=cgpaInp.getText().toString();
                double n=0.00;
                if(!gotText.isEmpty()) {
                    n=Float.parseFloat(gotText);
                }
                if(!(n>=0 && n<=4.00 && gotText.length()<=4)) {
                    cgpaInp.requestFocus();
                    cgpaInp.setText("");
                    cgpaInp.setError("The number must be between 0.00 to 4.00 and length shouldn't cross 5");
                }
                pointCGPA[serial]=n;
            }

            @Override
            public void afterTextChanged(Editable s) {

            }
        });
    }

    void setPointOnGradeChange(Spinner spGrade,TextView tvPoints,int subIndex) {
        spGrade.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                switch(position) {
                    case A4:
                        letterGrades[subIndex]="A";
                        pointSGPA[subIndex]=4.0;
                        tvPoints.setText(String.valueOf(pointSGPA[subIndex]));
                        break;
                    case Bpos37:
                        letterGrades[subIndex]="B+";
                        pointSGPA[subIndex]=3.7;
                        tvPoints.setText(String.valueOf(pointSGPA[subIndex]));
                        break;
                    case B34:
                        letterGrades[subIndex]="B";
                        pointSGPA[subIndex]=3.4;
                        tvPoints.setText(String.valueOf(pointSGPA[subIndex]));
                        break;
                    case Bneg31:
                        letterGrades[subIndex]="B-";
                        pointSGPA[subIndex]=3.1;
                        tvPoints.setText(String.valueOf(pointSGPA[subIndex]));
                        break;
                    case Cpos28:
                        letterGrades[subIndex]="C+";
                        pointSGPA[subIndex]=2.8;
                        tvPoints.setText(String.valueOf(pointSGPA[subIndex]));
                        break;
                    case C25:
                        letterGrades[subIndex]="C";
                        pointSGPA[subIndex]=2.5;
                        tvPoints.setText(String.valueOf(pointSGPA[subIndex]));
                        break;
                    case Cneg22:
                        letterGrades[subIndex]="C-";
                        pointSGPA[subIndex]=2.2;
                        tvPoints.setText(String.valueOf(pointSGPA[subIndex]));
                        break;
                    case Dpos15:
                        letterGrades[subIndex]="D+";
                        pointSGPA[subIndex]=1.5;
                        tvPoints.setText(String.valueOf(pointSGPA[subIndex]));
                        break;
                    case D1:
                        letterGrades[subIndex]="D";
                        pointSGPA[subIndex]=1.0;
                        tvPoints.setText(String.valueOf(pointSGPA[subIndex]));
                        break;
                    case F0:
                        letterGrades[subIndex]="F";
                        pointSGPA[subIndex]=0.0;
                        tvPoints.setText(String.valueOf(pointSGPA[subIndex]));
                        break;

                }
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {

            }
        });
    }

    void setGradeAndPointOnMarkChange(EditText etMark,Spinner spGrade,TextView tvPoints) {
        etMark.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {

            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {


                String gotText=etMark.getText().toString();
                int n=0;
                if(!gotText.isEmpty()) {
                    n=Integer.parseInt(gotText);
                }
                if(!(n>=0 && n<=100 && gotText.length()<=3)) {
                    etMark.requestFocus();
                    etMark.setText("");
                    etMark.setError("The number must be between 0 to 100");
                    spGrade.setSelection(F0);
                    tvPoints.setText("0.0");
                }
                else {
                    if(n>=90) {
                        spGrade.setSelection(A4);
                    }
                    else if (n>=87) {
                        spGrade.setSelection(Bpos37);
                    }
                    else if (n>=84) {
                        spGrade.setSelection(B34);
                    }
                    else if (n>=80) {
                        spGrade.setSelection(Bneg31);
                    }
                    else if (n>=77) {
                        spGrade.setSelection(Cpos28);
                    }
                    else if (n>=74) {
                        spGrade.setSelection(C25);
                    }
                    else if (n>=70) {
                        spGrade.setSelection(Cneg22);
                    }
                    else if (n>=65) {
                        spGrade.setSelection(Dpos15);
                    }
                    else if (n>=60) {
                        spGrade.setSelection(D1);
                    }
                    else {
                        spGrade.setSelection(F0);
                    }

                }


            }

            @Override
            public void afterTextChanged(Editable s) {

            }
        });

    }
    void windowAction(String msg,boolean autoHide) {
        handleWindow.removeCallbacks(runHideWindow);
        tvMsg.setText(msg);
        loutWindow.setVisibility(View.VISIBLE);
        if (autoHide) {
            btHideMsg.setVisibility(View.INVISIBLE); handleWindow.postDelayed(runHideWindow,3000);
        }
        else btHideMsg.setVisibility(View.VISIBLE);
    }


    void sgpaLoutSetup() {
        loutCGPA.setVisibility(View.GONE);
        loutCGPAheader.setVisibility(View.GONE);
        loutSGPA.setVisibility(View.VISIBLE);
        loutSGPAheader.setVisibility(View.VISIBLE);
        loutSub3.setVisibility(View.INVISIBLE);
        loutSub4.setVisibility(View.INVISIBLE);
        loutSub5.setVisibility(View.INVISIBLE);
        loutSub6.setVisibility(View.INVISIBLE);

    }

    void cgpaLoutSetup() {
        loutSGPA.setVisibility(View.GONE);
        loutSGPAheader.setVisibility(View.GONE);
        loutCGPA.setVisibility(View.VISIBLE);
        loutCGPAheader.setVisibility(View.VISIBLE);
        loutSem3.setVisibility(View.INVISIBLE);
        loutSem4.setVisibility(View.INVISIBLE);
        loutSem5.setVisibility(View.INVISIBLE);
        loutSem6.setVisibility(View.INVISIBLE);
        loutSem7.setVisibility(View.INVISIBLE);
        loutSem8.setVisibility(View.INVISIBLE);
        loutSem9.setVisibility(View.INVISIBLE);
        loutSem10.setVisibility(View.INVISIBLE);
        loutSem11.setVisibility(View.INVISIBLE);
        loutSem12.setVisibility(View.INVISIBLE);
    }




    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,WindowManager.LayoutParams.FLAG_FULLSCREEN);
        Objects.requireNonNull(getSupportActionBar()).hide();

        setContentView(R.layout.activity_grade_calculator);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);

        initialize();

        spGrd1.setSelection(F0);
        spGrd2.setSelection(F0);
        spGrd3.setSelection(F0);
        spGrd4.setSelection(F0);
        spGrd5.setSelection(F0);
        spGrd6.setSelection(F0);

        loutWindow.setVisibility(View.INVISIBLE);


        loutCGPAheader.setVisibility(View.GONE);

        setGradeAndPointOnMarkChange(etSub1,spGrd1,tvPnt1);
        setGradeAndPointOnMarkChange(etSub2,spGrd2,tvPnt2);
        setGradeAndPointOnMarkChange(etSub3,spGrd3,tvPnt3);
        setGradeAndPointOnMarkChange(etSub4,spGrd4,tvPnt4);
        setGradeAndPointOnMarkChange(etSub5,spGrd5,tvPnt5);
        setGradeAndPointOnMarkChange(etSub6,spGrd6,tvPnt6);

        setPointOnGradeChange(spGrd1,tvPnt1,s1);
        setPointOnGradeChange(spGrd2,tvPnt2,s2);
        setPointOnGradeChange(spGrd3,tvPnt3,s3);
        setPointOnGradeChange(spGrd4,tvPnt4,s4);
        setPointOnGradeChange(spGrd5,tvPnt5,s5);
        setPointOnGradeChange(spGrd6,tvPnt6,s6);

        setCrHours(spCrh1,s1);
        setCrHours(spCrh2,s2);
        setCrHours(spCrh3,s3);
        setCrHours(spCrh4,s4);
        setCrHours(spCrh5,s5);
        setCrHours(spCrh6,s6);

        setCrHours(spCrhSem1,0);
        setCrHours(spCrhSem2,1);
        setCrHours(spCrhSem3,2);
        setCrHours(spCrhSem4,3);
        setCrHours(spCrhSem5,4);
        setCrHours(spCrhSem6,5);
        setCrHours(spCrhSem7,6);
        setCrHours(spCrhSem8,7);
        setCrHours(spCrhSem9,8);
        setCrHours(spCrhSem10,9);
        setCrHours(spCrhSem11,10);
        setCrHours(spCrhSem12,11);

        cgpaInputManage(etSem1,0);
        cgpaInputManage(etSem2,1);
        cgpaInputManage(etSem3,2);
        cgpaInputManage(etSem4,3);
        cgpaInputManage(etSem5,4);
        cgpaInputManage(etSem6,5);
        cgpaInputManage(etSem7,6);
        cgpaInputManage(etSem8,7);
        cgpaInputManage(etSem9,8);
        cgpaInputManage(etSem10,9);
        cgpaInputManage(etSem11,10);
        cgpaInputManage(etSem12,11);

        sgpaLoutSetup();

        btAuthor.setOnClickListener(v -> {
                String url = "https://drive.google.com/file/d/1an9lkCktB_Xp8pB7apK5-rOPZFG3xNs5/view?usp=sharing";

                Intent i = new Intent(Intent.ACTION_VIEW);
                i.setData(Uri.parse(url));
                startActivity(i);

        });



        btAdd.setOnClickListener(v -> {
            if(sgpaMode) {
                boolean subAdded=true;
                switch (loutsSGPAvisible) {
                    case 2:
                        loutSub3.setVisibility(View.VISIBLE);
                        break;
                    case 3:
                        loutSub4.setVisibility(View.VISIBLE);
                        break;
                    case 4:
                        loutSub5.setVisibility(View.VISIBLE);
                        break;
                    case 5:
                        loutSub6.setVisibility(View.VISIBLE);
                        break;
                    default:
                        subAdded=false;
                        windowAction("A single semester can't contain more than 6 subjects",true);
                }
                loutsSGPAvisible++;
                if(subAdded) {
                    windowAction("New subject : Subject "+ loutsSGPAvisible+"\nhas been added successfully",true);
                }
            }
            else {
                boolean semAdded=true;
                switch (loutsCGPAvisible) {
                    case 2:
                        loutSem3.setVisibility(View.VISIBLE);
                        break;
                    case 3:
                        loutSem4.setVisibility(View.VISIBLE);
                        break;
                    case 4:
                        loutSem5.setVisibility(View.VISIBLE);
                        break;
                    case 5:
                        loutSem6.setVisibility(View.VISIBLE);
                        break;
                    case 6:
                        loutSem7.setVisibility(View.VISIBLE);
                        break;
                    case 7:
                        loutSem8.setVisibility(View.VISIBLE);
                        break;
                    case 8:
                        loutSem9.setVisibility(View.VISIBLE);
                        break;
                    case 9:
                        loutSem10.setVisibility(View.VISIBLE);
                        break;
                    case 10:
                        loutSem11.setVisibility(View.VISIBLE);
                        break;
                    case 11:
                        loutSem12.setVisibility(View.VISIBLE);
                        break;
                    default:
                        semAdded=false;
                        windowAction("More than 12 semester is unavailable",true);
                }
                loutsCGPAvisible++;
                if(semAdded) {
                    windowAction("New semester : Semester "+ loutsCGPAvisible+"\nhas been added successfully",true);
                }

            }

        });
        btHideMsg.setOnClickListener(v -> {
            loutWindow.setVisibility(View.INVISIBLE);
            handleWindow.removeCallbacks(runHideWindow);
        });

        btRefresh.setOnClickListener(v -> {
            if(sgpaMode) {
                sgpaLoutSetup();

                loutsSGPAvisible=2;

                etSub1.setText("0");
                etSub2.setText("0");
                etSub3.setText("0");
                etSub4.setText("0");
                etSub5.setText("0");
                etSub6.setText("0");

                spCrh1.setSelection(0);
                spCrh2.setSelection(0);
                spCrh3.setSelection(0);
                spCrh4.setSelection(0);
                spCrh5.setSelection(0);
                spCrh6.setSelection(0);

                tvPnt1.setText("0.0");
                tvPnt2.setText("0.0");
                tvPnt3.setText("0.0");
                tvPnt4.setText("0.0");
                tvPnt5.setText("0.0");
                tvPnt6.setText("0.0");

                for(int i=0;i<6;i++) {
                    letterGrades[i]="F";
                    pointSGPA[i]=0;
                    crHoursSGPA[i]=0;
                }

            }
            else {
                cgpaLoutSetup();

                loutsCGPAvisible=2;

                etSem1.setText("0");
                etSem2.setText("0");
                etSem3.setText("0");
                etSem4.setText("0");
                etSem5.setText("0");
                etSem6.setText("0");
                etSem7.setText("0");
                etSem8.setText("0");
                etSem9.setText("0");
                etSem10.setText("0");
                etSem11.setText("0");
                etSem12.setText("0");

                spCrhSem1.setSelection(0);
                spCrhSem2.setSelection(0);
                spCrhSem3.setSelection(0);
                spCrhSem4.setSelection(0);
                spCrhSem5.setSelection(0);
                spCrhSem6.setSelection(0);
                spCrhSem7.setSelection(0);
                spCrhSem8.setSelection(0);
                spCrhSem9.setSelection(0);
                spCrhSem10.setSelection(0);
                spCrhSem11.setSelection(0);
                spCrhSem12.setSelection(0);

                tvPnt1.setText("0.0");
                tvPnt2.setText("0.0");
                tvPnt3.setText("0.0");
                tvPnt4.setText("0.0");
                tvPnt5.setText("0.0");
                tvPnt6.setText("0.0");

                for(int i=0;i<12;i++) {
                    pointCGPA[i]=0;
                    crHoursCGPA[i]=0;
                }

            }
            windowAction("Refresh successful",true);
        });



        btCalcSGPA.setOnClickListener(v -> {

            if(sgpaMode) {

                if(cHoursArent0()) {
                    sgpa= (pointSGPA[s1]* crHoursSGPA[s1]+pointSGPA[s2]* crHoursSGPA[s2]+pointSGPA[s3]* crHoursSGPA[s3]+pointSGPA[s4]* crHoursSGPA[s4]+pointSGPA[s5]* crHoursSGPA[s5]+pointSGPA[s6]* crHoursSGPA[s6])/(float)(crHoursSGPA[s1]+ crHoursSGPA[s2]+ crHoursSGPA[s3]+ crHoursSGPA[s4]+ crHoursSGPA[s5]+ crHoursSGPA[s6]);



                    //Process : 1

                /*
                String point2f="",pointInStr=String.valueOf(sgpa);

                if(pointInStr.length()>=4) {
                    for (int i = 0; i < 4; i++) {
                        point2f += String.valueOf(pointInStr.charAt(i));
                    }
                    windowAction(String.format("Semester GPA : %s", point2f),false);
                }
                else {
                    windowAction(String.format("Semester GPA : %s", pointInStr),false);
                }


                */

                    //Process 2 : Recommended

                    String sgpa2f=String.valueOf(sgpa);
                    String b="",c="",d="", a=String.valueOf(sgpa2f.charAt(0));

                    if(sgpa2f.length()>=4) {
                        b=String.valueOf(sgpa2f.charAt(1));
                        c=String.valueOf(sgpa2f.charAt(2));
                        d=String.valueOf(sgpa2f.charAt(3));
                        sgpa2f=a+b+c+d;
                    }
                    windowAction(String.format("Semester GPA : %s\nStatus : %s", sgpa2f,status(Integer.parseInt(a))),false);





                }
                else {
                    windowAction("You have to select at least 2 subjects with credit hours more than 0",true);
                }



            }
            else {
                sgpaMode=true;
                btAdd.setText("Add subject");
                sgpaLoutSetup();
                windowAction("Switched to SGPA calculator mode",true);
            }

        });


        btCalcCGPA.setOnClickListener(v -> {
            if(!sgpaMode) {

                int crHsum=0;
                for(int i=0;i<12;i++) {
                    crHsum+=crHoursCGPA[i];
                }
                //Continue code here. Task left : Calculate cgpa
                if (cHoursArent0()) {
                    cgpa=(pointCGPA[0]*crHoursCGPA[0]+pointCGPA[1]*crHoursCGPA[1]+pointCGPA[2]*crHoursCGPA[2]+pointCGPA[3]*crHoursCGPA[3]+pointCGPA[4]*crHoursCGPA[4]+pointCGPA[5]*crHoursCGPA[5]+pointCGPA[6]*crHoursCGPA[6]+pointCGPA[7]*crHoursCGPA[7]+pointCGPA[8]*crHoursCGPA[8]+pointCGPA[9]*crHoursCGPA[9]+pointCGPA[10]*crHoursCGPA[10]+pointCGPA[11]*crHoursCGPA[11])/crHsum;
                    //Unchecked. Need to check if there is any bug
                    String cgpa2f=String.valueOf(cgpa);
                    String b="",c="",d="", a=String.valueOf(cgpa2f.charAt(0));

                    if(cgpa2f.length()>=4) {
                        b=String.valueOf(cgpa2f.charAt(1));
                        c=String.valueOf(cgpa2f.charAt(2));
                        d=String.valueOf(cgpa2f.charAt(3));
                        cgpa2f=a+b+c+d;
                    }
                    windowAction(String.format("Semester GPA : %s\nStatus : %s", cgpa2f,status(Integer.parseInt(a))),false);



                }
                else {
                    //Continue task here
                    windowAction("You have to select at least 2 semesters with credit hours more than 0",true);

                }


            }
            else {
                sgpaMode=false;
                btAdd.setText("Add semester");
                cgpaLoutSetup();
                windowAction("Switched to CGPA calculator mode",true);

            }

        });


    }





}
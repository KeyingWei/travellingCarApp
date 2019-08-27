#include "widget.h"
#include "ui_widget.h"
#include "synchapi.h"
#include "switch_button.h"
#include "QAbstractButton"


/*设置不同功能按键的样式表*/
QString open_button_style = "QPushButton{background-color:green;\
                                   color: white;   border-radius: 2px;  border: 1px groove gray;\
                                   border-style: outset;}";
QString close_button_style = "QPushButton{background-color:red;\
                             color: white;   border-radius: 2px;  border: 1px groove gray;\
                             border-style: outset;}";

                                 //  "QPushButton:hover{background-color:white; color: black;}"\
                                     "QPushButton:pressed{background-color:rgb(85, 170, 255);\
                                     border-style: inset; }";

 QString set_button_style = "QPushButton{background-color:green;\
                              color: white;   border-radius: 2px;  border: 1px groove gray;\
                              border-style: outset;}"\
                              "QPushButton:hover{background-color:white; color: black;}"\
                              "QPushButton:pressed{background-color:rgb(85, 170, 255);\
                              border-style: inset; }";



 QString mode_select = "QPushButton{background-color:blue;\
                             color: white;\
                               }";
 QString mode_deselect = "QPushButton{background-color:gray;\
                             color: black;\
                               }";


 //led label 样式表
 const QString m_red_SheetStyle = "min-width: 16px; min-height: 16px;max-width:16px; max-height: 16px;border-radius: 8px;  border:1px solid red;background:red";

 const QString m_green_SheetStyle = "min-width: 16px; min-height: 16px;max-width:16px; max-height: 16px;border-radius: 8px;  border:1px solid green;background:green";

 const QString m_grey_SheetStyle = "min-width: 16px; min-height: 16px;max-width:16px; max-height: 16px;border-radius: 8px;  border:1px solid gray;background:grey";

 const QString m_yellow_SheetStyle = "min-width: 16px; min-height: 16px;max-width:16px; max-height: 16px;border-radius: 8px;  border:1px solid yellow;background:yellow";


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);


      steering_mode_btn_grp =  new QButtonGroup(this);
      steering_mode_btn_grp->setExclusive(true);
      steering_mode_btn_grp->addButton(ui->steering_eps_mode_radio_btn);
      steering_mode_btn_grp->addButton(ui->steering_auto_mode_radio_Btn);
      steering_mode_btn_grp->addButton(ui->steering_standby_mode_radio_btn);
      steering_mode_btn_grp->addButton(ui->steering_auto_test_mode_radio_btn);
      steering_mode_btn_grp->addButton(ui->steering_manu_recovery_mode_radio_btn);
      connect(steering_mode_btn_grp,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(SteeringModeChange(QAbstractButton*)));


      driving_mode_btn_grp =  new QButtonGroup(this);
      driving_mode_btn_grp->setExclusive(true);
      driving_mode_btn_grp->addButton(ui->driving_ecu_mode_radio_btn);
      driving_mode_btn_grp->addButton(ui->driving_auto_mode_radio_Btn_2);
      driving_mode_btn_grp->addButton(ui->driving_auto_test_mode_radio_btn);
      driving_mode_btn_grp->addButton(ui->driving_standby_mode_radio_btn_2);
      driving_mode_btn_grp->addButton(ui->driving_manu_recovery_mode_radio_btn);
      connect(driving_mode_btn_grp,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(DrivingModeChange(QAbstractButton*)));

      braking_mode_btn_grp =  new QButtonGroup(this);
      braking_mode_btn_grp->setExclusive(true);
      braking_mode_btn_grp->addButton(ui->braking_eps_mode_radio_btn_2);
      braking_mode_btn_grp->addButton(ui->braking_auto_mode_radio_Btn_2);
      braking_mode_btn_grp->addButton(ui->braking_standby_mode_radio_btn_2);
      braking_mode_btn_grp->addButton(ui->braking_auto_test_mode_radio_btn_2);
      braking_mode_btn_grp->addButton(ui->braking_manu_recovery_mode_radio_btn_2);
      connect(braking_mode_btn_grp,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(BrakingModeChange(QAbstractButton*)));

      gear_mode_btn_grp =  new QButtonGroup(this);
      gear_mode_btn_grp->setExclusive(true);
      gear_mode_btn_grp->addButton(ui->gear_eps_mode_radio_btn_3);
      gear_mode_btn_grp->addButton(ui->gear_auto_mode_radio_Btn_3);
      gear_mode_btn_grp->addButton(ui->gear_standby_mode_radio_btn_3);
      gear_mode_btn_grp->addButton(ui->gear_auto_test_mode_radio_btn_3);
      gear_mode_btn_grp->addButton(ui->gear_manu_recovery_mode_radio_btn_3);
      connect(gear_mode_btn_grp,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(GearModeChange(QAbstractButton*)));

      lighting_mode_btn_grp =  new QButtonGroup(this);
      lighting_mode_btn_grp->setExclusive(true);
      lighting_mode_btn_grp->addButton(ui->light_eps_mode_radio_btn_3);
      lighting_mode_btn_grp->addButton(ui->light_auto_mode_radio_Btn_3);
      lighting_mode_btn_grp->addButton(ui->light_standby_mode_radio_btn_3);
      lighting_mode_btn_grp->addButton(ui->light_auto_test_mode_radio_btn_3);
      lighting_mode_btn_grp->addButton(ui->light_manu_recovery_mode_radio_btn_3);
      connect(lighting_mode_btn_grp,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(LightModeChange(QAbstractButton*)));

      parking_mode_btn_grp =  new QButtonGroup(this);
      parking_mode_btn_grp->setExclusive(true);
      parking_mode_btn_grp->addButton(ui->parking_eps_mode_radio_btn_4);
      parking_mode_btn_grp->addButton(ui->parking_auto_mode_radio_Btn_4);
      parking_mode_btn_grp->addButton(ui->parking_standby_mode_radio_btn_4);
      parking_mode_btn_grp->addButton(ui->parking_auto_test_mode_radio_btn_4);
      parking_mode_btn_grp->addButton(ui->parking_manu_recovery_mode_radio_btn_4);
      connect(parking_mode_btn_grp,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(ParkingModeChange(QAbstractButton*)));

    timer = new QTimer(this);//创建一个定时器
    connect(timer,&QTimer::timeout,this,&Widget::ScanfSerialPort);//信号连接
    //开启计时，100ms检测是否有串口设备接入
    timer->start(100);

    transmission = new myTransmission;

    timer1 = new QTimer(this);//创建一个定时器
    connect(timer1,&QTimer::timeout,this,&Widget::Dispaly_FeedBack);//信号连接
    timer1->start(50);

    check_connect_timer = new QTimer(this);//创建一个定时器
    connect(check_connect_timer,&QTimer::timeout,this,&Widget::CheckConnectStatus);//信号连接
    check_connect_timer->start(100);

    qApp->setStyle(QStyleFactory::create("Fusion"));
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(53,53,53));
    palette.setColor(QPalette::WindowText, Qt::gray);
    palette.setColor(QPalette::Base, QColor(15,15,15));
    palette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    palette.setColor(QPalette::ToolTipBase, Qt::white);
    palette.setColor(QPalette::ToolTipText, Qt::white);
    palette.setColor(QPalette::Text, Qt::white);
    palette.setColor(QPalette::Button, QColor(53,53,53));
    palette.setColor(QPalette::ButtonText, Qt::white);
    palette.setColor(QPalette::BrightText, Qt::red);
    palette.setColor(QPalette::Highlight, QColor(142,45,197).lighter());
    palette.setColor(QPalette::HighlightedText, Qt::black);
    qApp->setPalette(palette);


    ui->turning_feedback_mode->setReadOnly(true);
    ui->truning_feedback_crtl_value->setReadOnly(true);
    ui->accel_feedback_mode->setReadOnly(true);
    ui->accel_feedback_ctrl_value->setReadOnly(true);
    ui->brake_feedback_mode->setReadOnly(true);
    ui->brake_feedback_crtl_value->setReadOnly(true);
    ui->gear_feedback_mode->setReadOnly(true);
    ui->gear_feedback_crtl_value->setReadOnly(true);
    ui->parking_feedback_mode->setReadOnly(true);
    ui->parking_feedbakc_crtl_value->setReadOnly(true);
    ui->light_feedback_mode->setReadOnly(true);
    ui->light_feedback_crtl_value->setReadOnly(true);
    ui->system_data_speed_2->setReadOnly(true);
    ui->system_data_vol_2->setReadOnly(true);


   connect(ui->trunning_angle_add1,&QPushButton::clicked,this,&Widget::OnSteeringAngleAdd1Click);
   connect(ui->trunning_angle_add100,&QPushButton::clicked,this,&Widget::OnSteeringAngleAdd100Click);
   connect(ui->trunning_angle_sub1,&QPushButton::clicked,this,&Widget::OnSteeringAngleSub1Click);
   connect(ui->trunning_angle_sub100,&QPushButton::clicked,this,&Widget::OnSteeringAngleSub100Click);

   connect(ui->trunning_speed_add1,&QPushButton::clicked,this,&Widget::OnSteeringSpeedAdd1Click);
   connect(ui->trunning_speed_add100,&QPushButton::clicked,this,&Widget::OnSteeringSpeedAdd100Click);
   connect(ui->trunning_speed_sub1,&QPushButton::clicked,this,&Widget::OnSteeringSpeedSub1Click);
   connect(ui->trunning_speed_sub100,&QPushButton::clicked,this,&Widget::OnSteeringSpeedSub100Click);
   connect(ui->steering_cali_cmd,&QPushButton::clicked,this,&Widget::OnSteeringCaliCmdClick);

   connect(ui->accelerator_add1,&QPushButton::clicked,this,&Widget::OnAccelADD1Click);
   connect(ui->accelerator_add10,&QPushButton::clicked,this,&Widget::OnAccelAdd10Click);
   connect(ui->accelerator_sub1,&QPushButton::clicked,this,&Widget::OnAccelSub1Click);
   connect(ui->accelerator_sub10,&QPushButton::clicked,this,&Widget::OnAccelSub10Click);

   connect(ui->brake_add1,&QPushButton::clicked,this,&Widget::OnBrakeADD1Click);
   connect(ui->brake_add10,&QPushButton::clicked,this,&Widget::OnBrakeAdd10Click);
   connect(ui->brake_sub1,&QPushButton::clicked,this,&Widget::OnBrakeSub1Click);
   connect(ui->brake_sub10,&QPushButton::clicked,this,&Widget::OnBrakesub10Click);

   connect(ui->trunning_angle_edit,&QLineEdit::editingFinished,this,&Widget::LineEditChangeSteeringAngle);
   connect(ui->trunning_speed_edit,&QLineEdit::editingFinished,this,&Widget::LineEditChangeSteeringSpeed);
   connect(ui->accelerator_edit,&QLineEdit::editingFinished,this,&Widget::LineEditChangeAccel);
   connect(ui->brake_edit,&QLineEdit::editingFinished,this,&Widget::SLineEditChangeBrake);

   connect(ui->trunning_angle_slider,SIGNAL(valueChanged(int)),this,SLOT(SlideChangeSteeringAngle(int)));
   connect(ui->trunning_speed_slider,SIGNAL(valueChanged(int)),this,SLOT(SlideChangeSteeringSpeed(int)));
   connect(ui->accelerator_slider,SIGNAL(valueChanged(int)),this,SLOT(SlideChangeAccel(int)));
   connect(ui->brake_slider,SIGNAL(valueChanged(int)),this,SLOT(SlideChangeBrake(int)));


   ui->trunning_angle_slider->setRange(-2666,2666);
   ui->trunning_speed_slider->setRange(0,30);
   ui->accelerator_slider->setRange(0,100);
   ui->brake_slider->setRange(0,100);

   ui->trunning_angle_slider->setValue(0);
   ui->trunning_speed_slider->setValue(0);
   ui->accelerator_slider->setValue(0);
   ui->brake_slider->setValue(0);

   ui->trunning_angle_edit->setText("0");
   ui->trunning_speed_edit->setText("0");
   ui->accelerator_edit->setText("0");
   ui->brake_edit->setText("0");

   enable_button(false);

   ui->horntest->setStyleSheet(set_button_style);

   ui->StartOrStopButton_5->setStyleSheet(set_button_style);

   ui->set_open_left_light->setText(tr("打开左向灯"));
   ui->set_open_left_light->setStyleSheet(open_button_style);

   ui->set_open_right_light->setText(tr("打开右向灯"));
   ui->set_open_right_light->setStyleSheet(open_button_style);

   ui->set_open_low_beam_light->setText(tr("打开近光灯"));
   ui->set_open_low_beam_light->setStyleSheet(open_button_style);

   ui->set_open_hight_beam_light->setText(tr("打开远光灯"));
   ui->set_open_hight_beam_light->setStyleSheet(open_button_style);

   ui->set_open_warning_light->setText(tr("打开警示灯"));
   ui->set_open_warning_light->setStyleSheet(open_button_style);

 //  ui->set_open_front_fog_light->setText(tr("打开前雾灯"));
  // ui->set_open_front_fog_light->setStyleSheet(open_button_style);

   ui->set_open_rear_fog_light->setText(tr("打开后雾灯"));
   ui->set_open_rear_fog_light->setStyleSheet(open_button_style);

   ui->set_close_all_lights->setText(tr("关闭所有灯光"));
   ui->set_close_all_lights->setStyleSheet(set_button_style);

   ui->set_open_parking->setText(tr("打开驻车"));
   ui->set_open_parking->setStyleSheet(open_button_style);

   ui->set_gear_forward->setStyleSheet(open_button_style);
   ui->set_gear_low->setStyleSheet(open_button_style);
   ui->set_gear_neutral->setStyleSheet(open_button_style);
   ui->set_grear_parking->setStyleSheet(open_button_style);
   ui->set_grear_reverse->setStyleSheet(open_button_style);
   ui->gear_clear->setStyleSheet(set_button_style);

   ui->label_6->openExternalLinks();
   ui->label_5->setStyleSheet("color:red;font: 12pt Arial;");

   ui->set_all_clear_manu_error->setStyleSheet(set_button_style);
   ui->set_all_ennter_auto->setStyleSheet(set_button_style);
   ui->set_all_enter_mode2->setStyleSheet(set_button_style);

   ui->steering_cali_cmd->setStyleSheet(set_button_style);
   ui->encoder_o_zero->setEnabled(false);

   key_ctrl_enable = false;
   ui->keyCtrlEnable_btn->setStyleSheet(open_button_style);

   setFocus();


}

Widget::~Widget()
{
    delete ui;
}

int Widget::ScanfSerialPort()
{

    static int serila_num_curr = 0,serial_num_last = 0;
    QList<QSerialPortInfo> infos = QSerialPortInfo::availablePorts();
    if(infos.isEmpty())
    {
         ui->PortNumber_5->clear();
         serila_num_curr = 0;
         ui->StartOrStopButton_5->setEnabled(false);
         enable_button(false);
         memset(&transmission->feedbackdata,0,sizeof (transmission->feedbackdata));
    }
    else
    {
       QStringList list;
       ui->StartOrStopButton_5->setEnabled(true);
       serial_num_last = serila_num_curr;
        foreach(QSerialPortInfo info,infos)
        {
             list << info.portName();
        }
        serila_num_curr = list.length();
         if(serila_num_curr != serial_num_last)
         {
             ui->PortNumber_5->clear();
             qSort(list.begin(),list.end());
             ui->PortNumber_5->addItems(list);
         }

    }

    return 0;
}

void Widget::enable_button(bool enable)
{
    ui->set_open_left_light->setEnabled(enable);
    ui->set_open_right_light->setEnabled(enable);

    ui->set_open_low_beam_light->setEnabled(enable);
    ui->set_open_hight_beam_light->setEnabled(enable);
    ui->set_open_warning_light->setEnabled(enable);
    //ui->set_open_front_fog_light->setEnabled(enable);
    ui->set_open_rear_fog_light->setEnabled(enable);
    ui->set_close_all_lights->setEnabled(enable);
    ui->set_close_all_lights->setEnabled(enable);
    ui->set_open_parking->setEnabled(enable);

   ui->set_gear_forward->setEnabled(enable);
   ui->set_gear_low->setEnabled(enable);
   ui->set_gear_neutral->setEnabled(enable);
   ui->set_grear_parking->setEnabled(enable);
   ui->set_grear_reverse->setEnabled(enable);
   ui->gear_clear->setEnabled(enable);

   ui->steering_eps_mode_radio_btn->setEnabled(enable);
   ui->steering_auto_mode_radio_Btn->setEnabled(enable);
   ui->steering_standby_mode_radio_btn->setEnabled(enable);
   ui->steering_auto_test_mode_radio_btn->setEnabled(enable);
   ui->steering_manu_recovery_mode_radio_btn->setEnabled(enable);


   ui->driving_ecu_mode_radio_btn->setEnabled(enable);
   ui->driving_auto_mode_radio_Btn_2->setEnabled(enable);
   ui->driving_auto_test_mode_radio_btn->setEnabled(enable);
   ui->driving_standby_mode_radio_btn_2->setEnabled(enable);
   ui->driving_manu_recovery_mode_radio_btn->setEnabled(enable);


   ui->gear_eps_mode_radio_btn_3->setEnabled(enable);
   ui->gear_auto_mode_radio_Btn_3->setEnabled(enable);
   ui->gear_standby_mode_radio_btn_3->setEnabled(enable);
   ui->gear_auto_test_mode_radio_btn_3->setEnabled(enable);
   ui->gear_manu_recovery_mode_radio_btn_3->setEnabled(enable);


   ui->parking_eps_mode_radio_btn_4->setEnabled(enable);
   ui->parking_auto_mode_radio_Btn_4->setEnabled(enable);
   ui->parking_standby_mode_radio_btn_4->setEnabled(enable);
   ui->parking_auto_test_mode_radio_btn_4->setEnabled(enable);
   ui->parking_manu_recovery_mode_radio_btn_4->setEnabled(enable);

   ui->light_eps_mode_radio_btn_3->setEnabled(enable);
   ui->light_auto_mode_radio_Btn_3->setEnabled(enable);
   ui->light_standby_mode_radio_btn_3->setEnabled(enable);
   ui->light_auto_test_mode_radio_btn_3->setEnabled(enable);
   ui->light_manu_recovery_mode_radio_btn_3->setEnabled(enable);

   ui->braking_eps_mode_radio_btn_2->setEnabled(enable);
   ui->braking_auto_mode_radio_Btn_2->setEnabled(enable);
   ui->braking_standby_mode_radio_btn_2->setEnabled(enable);
   ui->braking_manu_recovery_mode_radio_btn_2->setEnabled(enable);
   ui->braking_auto_test_mode_radio_btn_2->setEnabled(enable);

   ui->trunning_angle_slider->setEnabled(enable);
   ui->trunning_speed_slider->setEnabled(enable);
   ui->accelerator_slider->setEnabled(enable);
   ui->brake_slider->setEnabled(enable);

   ui->trunning_angle_edit->setEnabled(enable);
   ui->trunning_speed_edit->setEnabled(enable);
   ui->accelerator_edit->setEnabled(enable);
   ui->brake_edit->setEnabled(enable);

   ui->trunning_angle_add1->setEnabled(enable);
   ui->trunning_angle_add100->setEnabled(enable);
   ui->trunning_angle_sub1->setEnabled(enable);
   ui->trunning_angle_sub100->setEnabled(enable);

   ui->trunning_speed_add1->setEnabled(enable);
   ui->trunning_speed_add100->setEnabled(enable);
   ui->trunning_speed_sub1->setEnabled(enable);
   ui->trunning_speed_sub100->setEnabled(enable);

   ui->accelerator_add1->setEnabled(enable);
   ui->accelerator_add10->setEnabled(enable);
   ui->accelerator_sub1->setEnabled(enable);
   ui->accelerator_sub10->setEnabled(enable);

   ui->brake_add1->setEnabled(enable);
   ui->brake_add10->setEnabled(enable);
   ui->brake_sub1->setEnabled(enable);
   ui->brake_sub10->setEnabled(enable);


    ui->set_all_clear_manu_error->setEnabled(enable);
    ui->set_all_ennter_auto->setEnabled(enable);
    ui->set_all_enter_mode2->setEnabled(enable);

     ui->steering_cali_cmd->setEnabled(enable);
     ui->horntest->setEnabled(enable);
     ui->keyCtrlEnable_btn->setEnabled(enable);

}


void Widget::Dispaly_FeedBack()
{
    if(transmission->feedbackdata.can_bus_status == 1 && transmission->connect_status == 1)
    {
        ui->turning_feedback_mode->setText(QString::number(transmission->feedbackdata.steering_mode));
        ui->truning_feedback_crtl_value->setText(QString::number(transmission->feedbackdata.steering_value));
        ui->accel_feedback_mode->setText(QString::number(transmission->feedbackdata.accel_mode));
        ui->accel_feedback_ctrl_value->setText(QString::number(transmission->feedbackdata.accel_value));
        ui->brake_feedback_mode->setText(QString::number(transmission->feedbackdata.brake_mode));
        ui->brake_feedback_crtl_value->setText(QString::number(transmission->feedbackdata.brake_value));
        ui->gear_feedback_mode->setText(QString::number(transmission->feedbackdata.gear_mode));
        ui->gear_feedback_crtl_value->setText(QString::number(transmission->feedbackdata.gear_value));
        ui->parking_feedback_mode->setText(QString::number(transmission->feedbackdata.parking_mode));
        ui->parking_feedbakc_crtl_value->setText(QString::number(transmission->feedbackdata.parking_value));
        ui->light_feedback_mode->setText(QString::number(transmission->feedbackdata.light_mode));
        ui->light_feedback_crtl_value->setText(QString::number(transmission->feedbackdata.light_value));
        ui->system_data_vol_2->setText(QString::number(transmission->feedbackdata.battery_vol));
        ui->system_data_speed_2->setText(QString::number((qint16)transmission->feedbackdata.car_speed));
        ui->encoder_o_zero->setText(QString::number((quint16)transmission->feedbackdata.encoderOfzero));
        ui->truning_feedback_speed->setText(QString::number((qint16)transmission->feedbackdata.steering_speed));

//        AccordingFeedbackSetRadioMode(transmission->feedbackdata.light_mode,LightModule_e);
//        AccordingFeedbackSetRadioMode(transmission->feedbackdata.gear_mode,GearModule_e);
//        AccordingFeedbackSetRadioMode(transmission->feedbackdata.parking_mode,ParkingingMoudule_e);
//        AccordingFeedbackSetRadioMode(transmission->feedbackdata.brake_mode,BrakingMoudule_e);
//        AccordingFeedbackSetRadioMode(transmission->feedbackdata.accel_mode,DrivingMoudule_e);
//        AccordingFeedbackSetRadioMode(transmission->feedbackdata.steering_mode,SteeringMoudule_e);
    }

    if((transmission->feedbackdata.error_code & (1<<0)) != 0)
    {
        ui->enpower_can_comm_error->setStyleSheet(m_red_SheetStyle);
    }
    else {
         ui->enpower_can_comm_error->setStyleSheet(m_green_SheetStyle);
    }

    if((transmission->feedbackdata.error_code & (1<<1)) != 0)
    {
        ui->brake_can_comm_error->setStyleSheet(m_red_SheetStyle);
    }
    else {
         ui->brake_can_comm_error->setStyleSheet(m_green_SheetStyle);
    }

    if((transmission->feedbackdata.error_code & (1<<2)) != 0)
    {
        ui->steering_can_comm_error->setStyleSheet(m_red_SheetStyle);
    }
    else {
         ui->steering_can_comm_error->setStyleSheet(m_green_SheetStyle);
    }

    if((transmission->feedbackdata.error_code & (1<<3)) != 0)
    {
        ui->parking_can_comm_error->setStyleSheet(m_red_SheetStyle);
    }
    else {
         ui->parking_can_comm_error->setStyleSheet(m_green_SheetStyle);
    }

    if((transmission->feedbackdata.error_code & (1<<4)) != 0)
    {
        ui->heartbeat_stop_error->setStyleSheet(m_red_SheetStyle);
    }
    else {
         ui->heartbeat_stop_error->setStyleSheet(m_green_SheetStyle);
    }

    if((transmission->feedbackdata.error_code & (1<<5)) != 0)
    {
        ui->brake_motor_overcurrent_error->setStyleSheet(m_red_SheetStyle);
    }
    else {
         ui->brake_motor_overcurrent_error->setStyleSheet(m_green_SheetStyle);
    }

    if((transmission->feedbackdata.error_code & (1<<6)) != 0)
    {
        ui->brake_zero_sersor_error->setStyleSheet(m_red_SheetStyle);
    }
    else {
         ui->brake_zero_sersor_error->setStyleSheet(m_green_SheetStyle);
    }

    if((transmission->feedbackdata.error_code & (1<<7)) != 0)
    {
        ui->eps_selfcheck_error->setStyleSheet(m_red_SheetStyle);
    }
    else {
         ui->eps_selfcheck_error->setStyleSheet(m_green_SheetStyle);
    }

    if((transmission->feedbackdata.error_code & (1<<8)) != 0)
    {
        ui->eps_encoder_error->setStyleSheet(m_red_SheetStyle);
    }
    else {
         ui->eps_encoder_error->setStyleSheet(m_green_SheetStyle);
    }


    if((transmission->feedbackdata.error_code & (1<<9)) != 0)
    {
        ui->eps_motor_overcurrent_error->setStyleSheet(m_red_SheetStyle);
    }
    else {
         ui->eps_motor_overcurrent_error->setStyleSheet(m_green_SheetStyle);
    }

    if((transmission->feedbackdata.error_code & (1<<10)) != 0)
    {
        ui->parking_motor_overcurren_error->setStyleSheet(m_red_SheetStyle);
    }
    else {
         ui->parking_motor_overcurren_error->setStyleSheet(m_green_SheetStyle);
    }

    if((transmission->feedbackdata.error_code & (1<<11)) != 0)
    {
        ui->manu_ctrl_error->setStyleSheet(m_red_SheetStyle);
    }
    else {
         ui->manu_ctrl_error->setStyleSheet(m_green_SheetStyle);
    }

    if((transmission->feedbackdata.error_code & (1<<12)) != 0)
    {
        ui->cmd_overtime_error->setStyleSheet(m_red_SheetStyle);
    }
    else {
         ui->cmd_overtime_error->setStyleSheet(m_green_SheetStyle);
    }
}


void Widget::on_StartOrStopButton_5_clicked()
{
    if(ui->StartOrStopButton_5->text() == tr("打开串口"))
       {

            transmission->Open_Serial(ui->PortNumber_5->currentText(),ui->baudBox_5->currentText().toInt(),\
                                      ui->DataBitsBox_5->currentText().toInt(),ui->ParityBox_5->currentIndex(),ui->StopBitsBox_5->currentIndex());

            transmission->serial_stata = 1;

             enable_button(true);

             ui->baudBox_5->setEnabled(false);
             ui->StopBitsBox_5->setEnabled(false);
             ui->ParityBox_5->setEnabled(false);
             ui->DataBitsBox_5->setEnabled(false);
             ui->PortNumber_5->setEnabled(false);
             ui->StartOrStopButton_5->setText(tr("关闭串口"));
    }
    else
    {
        transmission->Close_Serial();
        transmission->serial_stata = 0;

        enable_button(false);
        memset(&transmission->feedbackdata,0,sizeof (transmission->feedbackdata));
        transmission->feedbackdata.error_code = 0xFFFF;

        ui->baudBox_5->setEnabled(true);
        ui->StopBitsBox_5->setEnabled(true);
        ui->ParityBox_5->setEnabled(true);
        ui->DataBitsBox_5->setEnabled(true);
        ui->PortNumber_5->setEnabled(true);
        ui->StartOrStopButton_5->setText(tr("打开串口"));
    }
}

void Widget::on_set_grear_parking_clicked()
{
    ui->set_gear_forward->setStyleSheet(open_button_style);
    ui->set_gear_low->setStyleSheet(open_button_style);
    ui->set_gear_neutral->setStyleSheet(open_button_style);
    ui->set_grear_parking->setStyleSheet(close_button_style);
    ui->set_grear_reverse->setStyleSheet(open_button_style);
    transmission->Send_cmd(0x42,1);
}

void Widget::on_set_grear_reverse_clicked()
{
    ui->set_gear_forward->setStyleSheet(open_button_style);
    ui->set_gear_low->setStyleSheet(open_button_style);
    ui->set_gear_neutral->setStyleSheet(open_button_style);
    ui->set_grear_parking->setStyleSheet(open_button_style);
    ui->set_grear_reverse->setStyleSheet(close_button_style);
    transmission->Send_cmd(0x42,2);
}

void Widget::on_set_gear_neutral_clicked()
{
    ui->set_gear_forward->setStyleSheet(open_button_style);
    ui->set_gear_low->setStyleSheet(open_button_style);
    ui->set_gear_neutral->setStyleSheet(close_button_style);
    ui->set_grear_parking->setStyleSheet(open_button_style);
    ui->set_grear_reverse->setStyleSheet(open_button_style);
    transmission->Send_cmd(0x42,3);
}

void Widget::on_set_gear_forward_clicked()
{
    ui->set_gear_forward->setStyleSheet(close_button_style);
    ui->set_gear_low->setStyleSheet(open_button_style);
    ui->set_gear_neutral->setStyleSheet(open_button_style);
    ui->set_grear_parking->setStyleSheet(open_button_style);
    ui->set_grear_reverse->setStyleSheet(open_button_style);
    transmission->Send_cmd(0x42,4);
}

void Widget::on_set_gear_low_clicked()
{
    ui->set_gear_forward->setStyleSheet(open_button_style);
    ui->set_gear_low->setStyleSheet(close_button_style);
    ui->set_gear_neutral->setStyleSheet(open_button_style);
    ui->set_grear_parking->setStyleSheet(open_button_style);
    ui->set_grear_reverse->setStyleSheet(open_button_style);
    transmission->Send_cmd(0x42,5);
}

void Widget::on_gear_clear_clicked()
{
    ui->set_gear_forward->setStyleSheet(open_button_style);
    ui->set_gear_low->setStyleSheet(open_button_style);
    ui->set_gear_neutral->setStyleSheet(open_button_style);
    ui->set_grear_parking->setStyleSheet(open_button_style);
    ui->set_grear_reverse->setStyleSheet(open_button_style);
    transmission->Send_cmd(0x42,0);
}


void Widget::on_set_open_left_light_clicked()
{
    if(ui->set_open_left_light->text() == tr("打开左向灯"))
     {

           light_crl_bits |= (1<<0);
           ui->set_open_left_light->setText(tr("关闭左向灯"));
           ui->set_open_left_light->setStyleSheet(close_button_style);
     }
    else
    {
          light_crl_bits &= ~(1<<0);
          ui->set_open_left_light->setText(tr("打开左向灯"));
          ui->set_open_left_light->setStyleSheet(open_button_style);

    }
    qDebug() << "Light_crt_bits="<<light_crl_bits;
    transmission->Send_cmd(0x62,light_crl_bits);
}

void Widget::on_set_open_low_beam_light_clicked()
{
    if(ui->set_open_low_beam_light->text() == tr("打开近光灯"))
     {
            light_crl_bits |= (1<<2);
           ui->set_open_low_beam_light->setText(tr("关闭近光灯"));
           ui->set_open_low_beam_light->setStyleSheet(close_button_style);
     }
    else
    {
        light_crl_bits &= ~(1<<2);
        ui->set_open_low_beam_light->setText(tr("打开近光灯"));
        ui->set_open_low_beam_light->setStyleSheet(open_button_style);
    }
     qDebug() << "Light_crt_bits="<<light_crl_bits;
   transmission->Send_cmd(0x62,light_crl_bits);
}

void Widget::on_set_open_front_fog_light_clicked()
{
//    if(ui->set_open_front_fog_light->text() == tr("打开前雾灯"))
//     {
//           light_crl_bits |= (1<<5);
//           ui->set_open_front_fog_light->setText(tr("关闭前雾灯"));
//           ui->set_open_front_fog_light->setStyleSheet(close_button_style);
//     }
//    else
//    {
//        light_crl_bits &= ~(1<<5);
//        ui->set_open_front_fog_light->setText(tr("打开前雾灯"));
//        ui->set_open_front_fog_light->setStyleSheet(open_button_style);
//    }
//     qDebug() << "Light_crt_bits="<<light_crl_bits;
//    transmission->Send_cmd(0x62,light_crl_bits);
}

void Widget::on_set_open_warning_light_clicked()
{
    if(ui->set_open_warning_light->text() == tr("打开警示灯"))
     {
         light_crl_bits |= (1<<4);
          ui->set_open_warning_light->setText(tr("关闭警示灯"));
          ui->set_open_warning_light->setStyleSheet(close_button_style);
     }
    else
    {
        light_crl_bits &= ~(1<<4);
        ui->set_open_warning_light->setText(tr("打开警示灯"));
        ui->set_open_warning_light->setStyleSheet(open_button_style);
    }
     qDebug() << "Light_crt_bits="<<light_crl_bits;
    transmission->Send_cmd(0x62,light_crl_bits);
}

void Widget::on_set_open_right_light_clicked()
{
    if(ui->set_open_right_light->text() == tr("打开右向灯"))
     {
         light_crl_bits |= (1<<1);
          ui->set_open_right_light->setText(tr("关闭右向灯"));
          ui->set_open_right_light->setStyleSheet(close_button_style);
     }
    else
    {
        light_crl_bits &= ~(1<<1);
        ui->set_open_right_light->setText(tr("打开右向灯"));
        ui->set_open_right_light->setStyleSheet(open_button_style);
    }
    qDebug() << "Light_crt_bits="<<light_crl_bits;
   transmission->Send_cmd(0x62,light_crl_bits);
}

void Widget::on_set_open_hight_beam_light_clicked()
{
    if(ui->set_open_hight_beam_light->text() == tr("打开远光灯"))
     {
           light_crl_bits |= (1<<3);
           ui->set_open_hight_beam_light->setText(tr("关闭远光灯"));
           ui->set_open_hight_beam_light->setStyleSheet(close_button_style);
     }
    else
    {
       light_crl_bits &= ~(1<<3);
        ui->set_open_hight_beam_light->setText(tr("打开远光灯"));
        ui->set_open_hight_beam_light->setStyleSheet(open_button_style);
    }
     qDebug() << "Light_crt_bits="<<light_crl_bits;
     transmission->Send_cmd(0x62,light_crl_bits);
}

void Widget::on_set_open_rear_fog_light_clicked()
{
    if(ui->set_open_rear_fog_light->text() == tr("打开后雾灯"))
     {
           light_crl_bits |= (1<<6);
           ui->set_open_rear_fog_light->setText(tr("关闭后雾灯"));
           ui->set_open_rear_fog_light->setStyleSheet(close_button_style);
     }
    else
    {
        light_crl_bits &= ~(1<<6);
        ui->set_open_rear_fog_light->setText(tr("打开后雾灯"));
        ui->set_open_rear_fog_light->setStyleSheet(open_button_style);
    }
     qDebug() << "Light_crt_bits="<<light_crl_bits;
     transmission->Send_cmd(0x62,light_crl_bits);
}

void Widget::on_set_close_all_lights_clicked()
{
    ui->set_open_left_light->setText(tr("打开左向灯"));
    ui->set_open_left_light->setStyleSheet(open_button_style);

    ui->set_open_right_light->setText(tr("打开右向灯"));
    ui->set_open_right_light->setStyleSheet(open_button_style);

    ui->set_open_low_beam_light->setText(tr("打开近光灯"));
    ui->set_open_low_beam_light->setStyleSheet(open_button_style);

    ui->set_open_hight_beam_light->setText(tr("打开远光灯"));
    ui->set_open_hight_beam_light->setStyleSheet(open_button_style);

    ui->set_open_warning_light->setText(tr("打开警示灯"));
    ui->set_open_warning_light->setStyleSheet(open_button_style);

//    ui->set_open_front_fog_light->setText(tr("打开前雾灯"));
//    ui->set_open_front_fog_light->setStyleSheet(open_button_style);

    ui->set_open_rear_fog_light->setText(tr("打开后雾灯"));
    ui->set_open_rear_fog_light->setStyleSheet(open_button_style);

    light_crl_bits  = 0;

     qDebug() << "Light_crt_bits="<<light_crl_bits;

    transmission->Send_cmd(0x62,light_crl_bits);
}

void Widget::on_set_open_parking_clicked()
{
    if(ui->set_open_parking->text() == tr("打开驻车"))
    {
         transmission->Send_cmd(0x52,1);
         ui->set_open_parking->setText(tr("关闭驻车"));
         ui->set_open_parking->setStyleSheet(close_button_style);
    }
    else
    {
       transmission->Send_cmd(0x52,0);
         ui->set_open_parking->setText(tr("打开驻车"));
        ui->set_open_parking->setStyleSheet(open_button_style);
    }
}

void Widget::OnSteeringAngleSub100Click()
{
    steering_angle  -= 100;

    if(steering_angle < -2666)
        steering_angle = -2666;

    ui->trunning_angle_slider->setValue(steering_angle);
    ui->trunning_angle_edit->setText(QString::number(steering_angle));
    transmission->Send_cmd(0x12,steering_angle);
}

void Widget::OnSteeringAngleSub1Click()
{
    steering_angle  -= 1;

    if(steering_angle <= -2666)
        steering_angle = -2666;

    ui->trunning_angle_slider->setValue(steering_angle);
    ui->trunning_angle_edit->setText(QString::number(steering_angle));
    transmission->Send_cmd(0x12,steering_angle);
}

void Widget::OnSteeringSpeedSub100Click()
{
    steering_speed  -= 10;

    if(steering_speed <= 0)
        steering_speed = 0;

    ui->trunning_speed_slider->setValue(steering_speed);
    ui->trunning_speed_edit->setText(QString::number(steering_speed));
    transmission->Send_cmd(0x13,steering_speed);
}

void Widget::OnSteeringSpeedSub1Click()
{
    steering_speed  -= 1;

    if(steering_speed <= 0)
        steering_speed = 0;

    ui->trunning_speed_slider->setValue(steering_speed);
    ui->trunning_speed_edit->setText(QString::number(steering_speed));
    transmission->Send_cmd(0x13,steering_speed);
}

void Widget::OnSteeringAngleAdd100Click()
{
    steering_angle  += 100;

    if(steering_angle > 2666)
        steering_angle = 2666;

    ui->trunning_angle_slider->setValue(steering_angle);
    ui->trunning_angle_edit->setText(QString::number(steering_angle));
    transmission->Send_cmd(0x12,steering_angle);
}

void Widget::OnSteeringAngleAdd1Click()
{
    steering_angle  += 1;

    if(steering_angle > 2666)
        steering_angle = 2666;

    ui->trunning_angle_slider->setValue(steering_angle);
    ui->trunning_angle_edit->setText(QString::number(steering_angle));
   transmission->Send_cmd(0x12,steering_angle);
}

void Widget::OnSteeringSpeedAdd100Click()
{
    steering_speed  += 10;

    if(steering_speed >= 250)
        steering_speed = 250;

    ui->trunning_speed_slider->setValue(steering_speed);
    ui->trunning_speed_edit->setText(QString::number(steering_speed));
 transmission->Send_cmd(0x13,steering_speed);
}

void Widget::OnSteeringSpeedAdd1Click()
{
    steering_speed  += 1;

    if(steering_speed >= 250)
        steering_speed = 250;

    ui->trunning_speed_slider->setValue(steering_speed);
    ui->trunning_speed_edit->setText(QString::number(steering_speed));
    transmission->Send_cmd(0x13,steering_speed);
}

void Widget::OnSteeringCaliCmdClick()
{
   transmission->Send_cmd(0x14,0x00);
   Sleep(200);
   transmission->Send_cmd(0x14,0xAA);
   Sleep(200);
   transmission->Send_cmd(0x14,0x00);
}

void Widget::OnAccelSub10Click()
{
    accel_val  -= 10;

    if(accel_val <= 0)
        accel_val = 0;

    ui->accelerator_slider->setValue(accel_val);
    ui->accelerator_edit->setText(QString::number(accel_val));
    transmission->Send_cmd(0x22,accel_val);
}

void Widget::OnAccelSub1Click()
{
    accel_val  -= 1;

    if(accel_val <= 0)
        accel_val = 0;

    ui->accelerator_slider->setValue(accel_val);
    ui->accelerator_edit->setText(QString::number(accel_val));
    transmission->Send_cmd(0x22,accel_val);
}

void Widget::OnAccelAdd10Click()
{
    accel_val  += 10;

    if(accel_val >= 100)
        accel_val = 100;

    ui->accelerator_slider->setValue(accel_val);
    ui->accelerator_edit->setText(QString::number(accel_val));
    transmission->Send_cmd(0x22,accel_val);
}

void Widget::OnAccelADD1Click()
{
    accel_val  += 1;

    if(accel_val >= 100)
        accel_val = 100;

    ui->accelerator_slider->setValue(accel_val);
    ui->accelerator_edit->setText(QString::number(accel_val));
    transmission->Send_cmd(0x22,accel_val);
}

void Widget::OnBrakesub10Click()
{
    brake_val  -= 10;

    if(brake_val <= 0)
        brake_val = 0;

    ui->brake_slider->setValue(brake_val);
    ui->brake_edit->setText(QString::number(brake_val));
    transmission->Send_cmd(0x32,brake_val);
}

void Widget::OnBrakeSub1Click()
{
    brake_val  -= 1;

    if(brake_val <= 0)
        brake_val = 0;

    ui->brake_slider->setValue(brake_val);
    ui->brake_edit->setText(QString::number(brake_val));
    transmission->Send_cmd(0x32,brake_val);
}

void Widget::OnBrakeAdd10Click()
{
    brake_val  += 10;

    if(brake_val >= 100)
        brake_val = 100;

    ui->brake_slider->setValue(brake_val);
    ui->brake_edit->setText(QString::number(brake_val));
    transmission->Send_cmd(0x32,brake_val);
}

void Widget::OnBrakeADD1Click()
{
    brake_val  += 1;

    if(brake_val >= 100)
        brake_val = 100;

    ui->brake_slider->setValue(brake_val);
    ui->brake_edit->setText(QString::number(brake_val));
    transmission->Send_cmd(0x32,brake_val);
}

void Widget::SlideChangeSteeringAngle(int value)
{
  steering_angle = value;
  ui->trunning_angle_edit->setText(QString::number(steering_angle));
   transmission->Send_cmd(0x12,steering_angle);
}

void Widget::SlideChangeSteeringSpeed(int value)
{
    steering_speed = value;
    ui->trunning_speed_edit->setText(QString::number(steering_speed));
    transmission->Send_cmd(0x13,steering_speed);
}

void Widget::SlideChangeAccel(int value)
{
    accel_val = value;
    ui->accelerator_edit->setText(QString::number(accel_val));
    transmission->Send_cmd(0x22,accel_val);
}

void Widget::SlideChangeBrake(int value)
{
    brake_val = value;
    ui->brake_edit->setText(QString::number(brake_val));
    transmission->Send_cmd(0x32,brake_val);
}

void Widget::LineEditChangeSteeringAngle()
{
   steering_angle = ui->trunning_angle_edit->text().toInt();
   ui->trunning_angle_slider->setValue(steering_angle);
    transmission->Send_cmd(0x12,steering_angle);
}

void Widget::LineEditChangeSteeringSpeed()
{
    steering_speed = ui->trunning_speed_edit->text().toInt();
    ui->trunning_speed_slider->setValue(steering_speed);
  transmission->Send_cmd(0x13,steering_speed);
}

void Widget::LineEditChangeAccel()
{
   accel_val = ui->accelerator_edit->text().toInt();
   ui->accelerator_slider->setValue(accel_val);
   transmission->Send_cmd(0x22,accel_val);
}

void Widget::SLineEditChangeBrake()
{
    brake_val = ui->brake_edit->text().toInt();
    ui->brake_slider->setValue(brake_val);
    transmission->Send_cmd(0x32,brake_val);
}

void Widget::CheckConnectStatus()
{
    transmission->connect_cnt++;

    if(transmission->connect_cnt >= 5)
    {
        transmission->connect_status = 0;
    }


   if(transmission->connect_status == 1)
   {
       if(transmission->can_bus_status == 1 || transmission->feedbackdata.can_bus_status == 1)
       {
           ui->label_5->setStyleSheet("color:green;font: 12pt Arial;");
           ui->label_5->setText(tr("串口连接正常,CAN连接正常"));
       }
       else
       {
            ui->label_5->setStyleSheet("color:yellow;font: 12pt Arial;");
         ui->label_5->setText(tr("串口连接正常,CAN未连接"));
       }
   }
   else
   {
        ui->label_5->setStyleSheet("color:red;font: 12pt Arial;");
        ui->label_5->setText(tr("串口未连接"));
   }
}

void Widget::on_set_all_ennter_auto_clicked()
{
    AccordingFeedbackSetRadioMode(1,LightModule_e);
    AccordingFeedbackSetRadioMode(1,GearModule_e);
    AccordingFeedbackSetRadioMode(1,ParkingingMoudule_e);
    AccordingFeedbackSetRadioMode(1,BrakingMoudule_e);
    AccordingFeedbackSetRadioMode(1,DrivingMoudule_e);
    AccordingFeedbackSetRadioMode(1,SteeringMoudule_e);

    transmission->Send_cmd(0x61,4);
}

void Widget::on_set_all_clear_manu_error_clicked()
{

    AccordingFeedbackSetRadioMode(3,LightModule_e);
    AccordingFeedbackSetRadioMode(3,GearModule_e);
    AccordingFeedbackSetRadioMode(3,ParkingingMoudule_e);
    AccordingFeedbackSetRadioMode(3,BrakingMoudule_e);
    AccordingFeedbackSetRadioMode(3,DrivingMoudule_e);
    AccordingFeedbackSetRadioMode(3,SteeringMoudule_e);
    transmission->Send_cmd(0x51,4);
}

void Widget::on_set_all_enter_mode2_clicked()
{
    transmission->Send_cmd(0x11,2);
    Sleep(10);
    transmission->Send_cmd(0x21,2);
     Sleep(10);
    transmission->Send_cmd(0x31,2);
     Sleep(10);
    transmission->Send_cmd(0x41,2);
     Sleep(10);
    transmission->Send_cmd(0x51,2);
     Sleep(10);
    transmission->Send_cmd(0x61,2);

     AccordingFeedbackSetRadioMode(2,LightModule_e);
     AccordingFeedbackSetRadioMode(2,GearModule_e);
     AccordingFeedbackSetRadioMode(2,ParkingingMoudule_e);
     AccordingFeedbackSetRadioMode(2,BrakingMoudule_e);
     AccordingFeedbackSetRadioMode(2,DrivingMoudule_e);
     AccordingFeedbackSetRadioMode(2,SteeringMoudule_e);
}


void Widget::SteeringModeChange(QAbstractButton* btn)
{
    // 遍历按钮，获取选中状态
     QList<QAbstractButton*> list = steering_mode_btn_grp->buttons();
     foreach (QAbstractButton *pButton, list)
     {
         if(pButton->isChecked())
           {
               if(strcmp(pButton->text().toUtf8(),"待机模式") == 0)
               {
                    transmission->Send_cmd(0x11,0);
                    qDebug() << "steering standby mode";
               }
               else if(strcmp(pButton->text().toUtf8(),"自动驾驶模式") == 0)
               {
                   transmission->Send_cmd(0x11,1);
                   qDebug() << "steering auto driver mode";
               }
               else if(strcmp(pButton->text().toUtf8(),"手动模式") == 0)
               {
                   transmission->Send_cmd(0x11,2);
                   qDebug() << "steering manu driver mode";
               }
               else if(strcmp(pButton->text().toUtf8(),"人工介入恢复模式") == 0)
               {
                   transmission->Send_cmd(0x11,3);
                   qDebug() << "steering manu recovery mode";
               }
               else if(strcmp(pButton->text().toUtf8(),"清除故障模式") == 0)
               {
                   transmission->Send_cmd(0x11,4);
                   qDebug() << "steering clear error mode";
               }
               else
               {
                    qDebug() << "button choice is error";
               }
           }
     }
}

void Widget::DrivingModeChange(QAbstractButton *)
{
    // 遍历按钮，获取选中状态
     QList<QAbstractButton*> list = driving_mode_btn_grp->buttons();
     foreach (QAbstractButton *pButton, list)
     {
         if(pButton->isChecked())
           {
               if(strcmp(pButton->text().toUtf8(),"待机模式") == 0)
               {
                    transmission->Send_cmd(0x21,0);
                    qDebug() << "driving standby mode";
               }
               else if(strcmp(pButton->text().toUtf8(),"自动驾驶模式") == 0)
               {
                   transmission->Send_cmd(0x21,1);
                   qDebug() << "driving auto driver mode";
               }
               else if(strcmp(pButton->text().toUtf8(),"手动模式") == 0)
               {
                   transmission->Send_cmd(0x21,2);
                   qDebug() << "driving manu driver mode";
               }
               else if(strcmp(pButton->text().toUtf8(),"人工介入恢复模式") == 0)
               {
                   transmission->Send_cmd(0x21,3);
                   qDebug() << "driving manu recovery mode";
               }
               else if(strcmp(pButton->text().toUtf8(),"清除故障模式") == 0)
               {
                   transmission->Send_cmd(0x21,4);
                   qDebug() << "driving clear error mode";
               }
               else
               {
                    qDebug() << "button choice is error";
               }
           }
     }
}

void Widget::BrakingModeChange(QAbstractButton *)
{
    // 遍历按钮，获取选中状态
     QList<QAbstractButton*> list = braking_mode_btn_grp->buttons();
     foreach (QAbstractButton *pButton, list)
     {
         if(pButton->isChecked())
           {
               if(strcmp(pButton->text().toUtf8(),"待机模式") == 0)
               {
                    transmission->Send_cmd(0x31,0);
                    qDebug() << "Braking standby mode";
               }
               else if(strcmp(pButton->text().toUtf8(),"自动驾驶模式") == 0)
               {
                   transmission->Send_cmd(0x31,1);
                   qDebug() << "Braking auto driver mode";
               }
               else if(strcmp(pButton->text().toUtf8(),"手动模式") == 0)
               {
                   transmission->Send_cmd(0x31,2);
                   qDebug() << "Braking manu driver mode";
               }
               else if(strcmp(pButton->text().toUtf8(),"人工介入恢复模式") == 0)
               {
                   transmission->Send_cmd(0x31,3);
                   qDebug() << "Braking manu recovery mode";
               }
               else if(strcmp(pButton->text().toUtf8(),"清除故障模式") == 0)
               {
                   transmission->Send_cmd(0x31,4);
                   qDebug() << "Braking clear error mode";
               }
               else
               {
                    qDebug() << "button choice is error";
               }
           }
     }
}

void Widget::LightModeChange(QAbstractButton *)
{
    // 遍历按钮，获取选中状态
     QList<QAbstractButton*> list = lighting_mode_btn_grp->buttons();
     foreach (QAbstractButton *pButton, list)
     {
         if(pButton->isChecked())
           {
               if(strcmp(pButton->text().toUtf8(),"待机模式") == 0)
               {
                    transmission->Send_cmd(0x61,0);
                    qDebug() << "Light standby mode";
               }
               else if(strcmp(pButton->text().toUtf8(),"自动驾驶模式") == 0)
               {
                   transmission->Send_cmd(0x61,1);
                   qDebug() << "Light auto driver mode";
               }
               else if(strcmp(pButton->text().toUtf8(),"手动模式") == 0)
               {
                   transmission->Send_cmd(0x61,2);
                   qDebug() << "Light manu driver mode";
               }
               else if(strcmp(pButton->text().toUtf8(),"人工介入恢复模式") == 0)
               {
                   transmission->Send_cmd(0x61,3);
                   qDebug() << "Light manu recovery mode";
               }
               else if(strcmp(pButton->text().toUtf8(),"清除故障模式") == 0)
               {
                   transmission->Send_cmd(0x61,4);
                   qDebug() << "Light clear error mode";
               }
               else
               {
                    qDebug() << "button choice is error";
               }
           }
     }
}

void Widget::ParkingModeChange(QAbstractButton *)
{
    // 遍历按钮，获取选中状态
     QList<QAbstractButton*> list = parking_mode_btn_grp->buttons();
     foreach (QAbstractButton *pButton, list)
     {
         if(pButton->isChecked())
           {
               if(strcmp(pButton->text().toUtf8(),"待机模式") == 0)
               {
                    transmission->Send_cmd(0x51,0);
                    qDebug() << "Parking standby mode";
               }
               else if(strcmp(pButton->text().toUtf8(),"自动驾驶模式") == 0)
               {
                   transmission->Send_cmd(0x51,1);
                   qDebug() << "Parking auto driver mode";
               }
               else if(strcmp(pButton->text().toUtf8(),"手动模式") == 0)
               {
                   transmission->Send_cmd(0x51,2);
                   qDebug() << "Parking manu driver mode";
               }
               else if(strcmp(pButton->text().toUtf8(),"人工介入恢复模式") == 0)
               {
                   transmission->Send_cmd(0x51,3);
                   qDebug() << "Parking manu recovery mode";
               }
               else if(strcmp(pButton->text().toUtf8(),"清除故障模式") == 0)
               {
                   transmission->Send_cmd(0x51,4);
                   qDebug() << "Parking clear error mode";
               }
               else
               {
                    qDebug() << "button choice is error";
               }
           }
     }
}

void Widget::GearModeChange(QAbstractButton *)
{
    // 遍历按钮，获取选中状态
     QList<QAbstractButton*> list = gear_mode_btn_grp->buttons();
     foreach (QAbstractButton *pButton, list)
     {
         if(pButton->isChecked())
           {
               if(strcmp(pButton->text().toUtf8(),"待机模式") == 0)
               {
                    transmission->Send_cmd(0x41,0);
                    qDebug() << "Gear standby mode";
               }
               else if(strcmp(pButton->text().toUtf8(),"自动驾驶模式") == 0)
               {
                   transmission->Send_cmd(0x41,1);
                   qDebug() << "Gear auto driver mode";
               }
               else if(strcmp(pButton->text().toUtf8(),"手动模式") == 0)
               {
                   transmission->Send_cmd(0x41,2);
                   qDebug() << "Gear manu driver mode";
               }
               else if(strcmp(pButton->text().toUtf8(),"人工介入恢复模式") == 0)
               {
                   transmission->Send_cmd(0x41,3);
                   qDebug() << "Gear manu recovery mode";
               }
               else if(strcmp(pButton->text().toUtf8(),"清除故障模式") == 0)
               {
                   transmission->Send_cmd(0x41,4);
                   qDebug() << "Gear clear error mode";
               }
               else
               {
                    qDebug() << "button choice is error";
               }
           }
     }
}

void Widget::on_horntest_clicked()
{
    light_crl_bits |= (1<<5);
    transmission->Send_cmd(0x62,light_crl_bits);
    qDebug() << "Light_crt_bits="<<light_crl_bits;
    Sleep(500);
    light_crl_bits &= ~(1<<5);
    qDebug() << "Light_crt_bits="<<light_crl_bits;
    transmission->Send_cmd(0x62,light_crl_bits);
}

void Widget::AccordingFeedbackSetRadioMode(uint8_t mode,uint8_t module)
{
    switch (module) {
    case SteeringMoudule_e:
        switch (mode) {
        case 0:
            ui->steering_standby_mode_radio_btn->setChecked(true);
            break;
        case 1:
            ui->steering_auto_mode_radio_Btn->setChecked(true);
            break;
        case 2:
            ui->steering_eps_mode_radio_btn->setChecked(true);
            break;
        case 3:
            ui->steering_manu_recovery_mode_radio_btn->setChecked(true);
            break;
        case 4:
            ui->steering_auto_test_mode_radio_btn->setChecked(true);
            break;
        default:
           ui->steering_standby_mode_radio_btn->setChecked(false);
           ui->steering_auto_mode_radio_Btn->setChecked(false);
           ui->steering_eps_mode_radio_btn->setChecked(false);
           ui->steering_manu_recovery_mode_radio_btn->setChecked(false);
           ui->steering_auto_test_mode_radio_btn->setChecked(false);
           break;
        }
        break;
    case DrivingMoudule_e:
        switch (mode) {
        case 0:
            ui->driving_standby_mode_radio_btn_2->setChecked(true);
            break;
        case 1:
            ui->driving_auto_mode_radio_Btn_2->setChecked(true);
            break;
        case 2:
            ui->driving_ecu_mode_radio_btn->setChecked(true);
            break;
        case 3:
            ui->driving_manu_recovery_mode_radio_btn->setChecked(true);
            break;
        case 4:
            ui->driving_auto_test_mode_radio_btn->setChecked(true);
            break;
        default:
           ui->driving_standby_mode_radio_btn_2->setChecked(false);
           ui->driving_auto_mode_radio_Btn_2->setChecked(false);
           ui->driving_ecu_mode_radio_btn->setChecked(false);
           ui->driving_manu_recovery_mode_radio_btn->setChecked(false);
           ui->driving_auto_test_mode_radio_btn->setChecked(false);
           break;
        }
        break;
    case BrakingMoudule_e:
        switch (mode) {
        case 0:
            ui->braking_standby_mode_radio_btn_2->setChecked(true);
            break;
        case 1:
            ui->braking_auto_mode_radio_Btn_2->setChecked(true);
            break;
        case 2:
            ui->braking_eps_mode_radio_btn_2->setChecked(true);
            break;
        case 3:
            ui->braking_manu_recovery_mode_radio_btn_2->setChecked(true);
            break;
        case 4:
            ui->braking_auto_test_mode_radio_btn_2->setChecked(true);
            break;
        default:
           ui->braking_standby_mode_radio_btn_2->setChecked(false);
           ui->braking_auto_mode_radio_Btn_2->setChecked(false);
           ui->braking_eps_mode_radio_btn_2->setChecked(false);
           ui->braking_manu_recovery_mode_radio_btn_2->setChecked(false);
           ui->braking_auto_test_mode_radio_btn_2->setChecked(false);
           break;
        }
        break;
    case ParkingingMoudule_e:
        switch (mode) {
        case 0:
            ui->parking_standby_mode_radio_btn_4->setChecked(true);
            break;
        case 1:
            ui->parking_auto_mode_radio_Btn_4->setChecked(true);
            break;
        case 2:
            ui->parking_eps_mode_radio_btn_4->setChecked(true);
            break;
        case 3:
            ui->parking_manu_recovery_mode_radio_btn_4->setChecked(true);
            break;
        case 4:
            ui->parking_auto_test_mode_radio_btn_4->setChecked(true);
            break;
        default:
           ui->parking_standby_mode_radio_btn_4->setChecked(false);
           ui->parking_auto_mode_radio_Btn_4->setChecked(false);
           ui->parking_manu_recovery_mode_radio_btn_4->setChecked(false);
           ui->parking_eps_mode_radio_btn_4->setChecked(false);
           ui->parking_auto_test_mode_radio_btn_4->setChecked(false);
           break;
        }
        break;
    case LightModule_e:
        switch (mode) {
        case 0:
            ui->light_standby_mode_radio_btn_3->setChecked(true);
            break;
        case 1:
            ui->light_auto_mode_radio_Btn_3->setChecked(true);
            break;
        case 2:
            ui->light_eps_mode_radio_btn_3->setChecked(true);
            break;
        case 3:
            ui->light_manu_recovery_mode_radio_btn_3->setChecked(true);
            break;
        case 4:
            ui->light_auto_test_mode_radio_btn_3->setChecked(true);
            break;
        default:
           ui->light_standby_mode_radio_btn_3->setChecked(false);
           ui->light_auto_mode_radio_Btn_3->setChecked(false);
           ui->light_manu_recovery_mode_radio_btn_3->setChecked(false);
           ui->light_eps_mode_radio_btn_3->setChecked(false);
           ui->light_auto_test_mode_radio_btn_3->setChecked(false);
           break;
        }
        break;
    case GearModule_e:
        switch (mode) {
        case 0:
            ui->gear_standby_mode_radio_btn_3->setChecked(true);
            break;
        case 1:
            ui->gear_auto_mode_radio_Btn_3->setChecked(true);
            break;
        case 2:
            ui->gear_eps_mode_radio_btn_3->setChecked(true);
            break;
        case 3:
            ui->gear_manu_recovery_mode_radio_btn_3->setChecked(true);
            break;
        case 4:
            ui->gear_auto_test_mode_radio_btn_3->setChecked(true);
            break;
        default:
           ui->gear_standby_mode_radio_btn_3->setChecked(false);
           ui->gear_auto_mode_radio_Btn_3->setChecked(false);
           ui->gear_manu_recovery_mode_radio_btn_3->setChecked(false);
           ui->gear_eps_mode_radio_btn_3->setChecked(false);
           ui->gear_auto_test_mode_radio_btn_3->setChecked(false);
           break;
        }
        break;
    }
}

bool key_w =  false;
bool key_s = false;
void Widget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
    {
       if(event->isAutoRepeat())
           return;

       if(transmission->feedbackdata.can_bus_status == 1 && key_ctrl_enable == true && transmission->connect_status == 1)
       {
           //油门和档位进入自动模式
           Sleep(50);
           transmission->Send_cmd(0x41,1);
           Sleep(50);
           transmission->Send_cmd(0x21,1);
           ui->driving_auto_mode_radio_Btn_2->setChecked(true);
           ui->gear_auto_mode_radio_Btn_3->setChecked(true);
           //设置档位为前进挡
           Sleep(50);
           on_set_gear_forward_clicked();
           //设置油门值为10%
           accel_val = 10;
           ui->accelerator_slider->setValue(accel_val);
           ui->accelerator_edit->setText(QString::number(accel_val));
           transmission->Send_cmd(0x22,accel_val);
           qDebug() << "gear: 4"<<"throttle:" << accel_val;
       }
       qDebug() << "key_w press";
    } else if(event->key() == Qt::Key_S)
    {
       if(event->isAutoRepeat())
           return;
       if(transmission->feedbackdata.can_bus_status == 1 && key_ctrl_enable == true && transmission->connect_status == 1)
       {
           //油门和档位进入自动模式
           Sleep(50);
           transmission->Send_cmd(0x41,1);
           Sleep(50);
           transmission->Send_cmd(0x21,1);
           ui->driving_auto_mode_radio_Btn_2->setChecked(true);
           ui->gear_auto_mode_radio_Btn_3->setChecked(true);
           //设置档位为前进挡
           Sleep(50);
           on_set_grear_reverse_clicked();
           //设置油门值为10%
           Sleep(50);
           DrivingModeChange((QAbstractButton *)driving_mode_btn_grp);
           accel_val = 10;
           ui->accelerator_slider->setValue(accel_val);
           ui->accelerator_edit->setText(QString::number(accel_val));
           transmission->Send_cmd(0x22,accel_val);

          qDebug() << "gear: 2"<<"throttle:" << accel_val;
       }
       qDebug() << "key_s press";
    }else  if(event->key() == Qt::Key_A)
    {
       if(event->isAutoRepeat())
       {
            qDebug() << "key_a press";
       }

    }else if(event->key() == Qt::Key_D)
    {
       if(event->isAutoRepeat())
       {
            qDebug() << "key_D press";
       }

    }
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
    {
       if(event->isAutoRepeat())
       {
           return;
       }

       if(transmission->feedbackdata.can_bus_status == 1 && key_ctrl_enable == true && transmission->connect_status == 1)
       {
           //油门和档位进入手动模式
           Sleep(50);
           transmission->Send_cmd(0x41,2);
           Sleep(50);
           transmission->Send_cmd(0x21,2);
           ui->driving_ecu_mode_radio_btn->setChecked(true);
           ui->gear_eps_mode_radio_btn_3->setChecked(true);
           //设置档位为空挡
           Sleep(50);
           on_set_gear_neutral_clicked();
           Sleep(100);
           accel_val = 0;
           ui->accelerator_slider->setValue(accel_val);
           ui->accelerator_edit->setText(QString::number(accel_val));
           transmission->Send_cmd(0x22,accel_val);
           qDebug() << "gear: 3"<<"throttle:" << accel_val;
       }
        qDebug() << "key_w release";
    } else if(event->key() == Qt::Key_S)
    {
       if(event->isAutoRepeat())
           return;
       if(transmission->feedbackdata.can_bus_status == 1 && key_ctrl_enable == true && transmission->connect_status == 1)
       {
           //油门和档位进入手动模式
           Sleep(50);
           transmission->Send_cmd(0x41,2);
           Sleep(50);
           transmission->Send_cmd(0x21,2);
           ui->driving_ecu_mode_radio_btn->setChecked(true);
           ui->gear_eps_mode_radio_btn_3->setChecked(true);
           //设置档位为空挡
           on_set_gear_neutral_clicked();
           Sleep(100);
           accel_val = 0;
           ui->accelerator_slider->setValue(accel_val);
           ui->accelerator_edit->setText(QString::number(accel_val));
           transmission->Send_cmd(0x22,accel_val);
           qDebug() << "gear: 3"<<"throttle:" << accel_val;
       }
        qDebug() << "key_s release";
    } else if(event->key() == Qt::Key_A)
    {
       if(event->isAutoRepeat())
           return;

         qDebug() << "key_a release";
    }else if(event->key() == Qt::Key_D)
    {
       if(event->isAutoRepeat())
           return;

         qDebug() << "key_D release";
    }
}

void Widget::on_keyCtrlEnable_btn_clicked()
{
    if(ui->keyCtrlEnable_btn->text() == "打开键盘控制")
    {
         ui->keyCtrlEnable_btn->setText("关闭键盘控制");
         ui->keyCtrlEnable_btn->setStyleSheet(close_button_style);
         key_ctrl_enable = true;
         setFocus();
    }
    else
    {
         ui->keyCtrlEnable_btn->setText("打开键盘控制");
         ui->keyCtrlEnable_btn->setStyleSheet(open_button_style);
         key_ctrl_enable = false;
    }
}

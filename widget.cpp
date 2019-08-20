#include "widget.h"
#include "ui_widget.h"
#include "synchapi.h"
#include "switch_button.h"
#include "QAbstractButton"


/*设置不同功能按键的样式表*/
QString open_button_style = "QPushButton{background-color:green;\
                                   color: white;   border-radius: 5px;  border: 2px groove gray;\
                                   border-style: outset;}";
QString close_button_style = "QPushButton{background-color:red;\
                             color: white;   border-radius: 5px;  border: 2px groove gray;\
                             border-style: outset;}";

                                 //  "QPushButton:hover{background-color:white; color: black;}"\
                                     "QPushButton:pressed{background-color:rgb(85, 170, 255);\
                                     border-style: inset; }";

 QString set_button_style = "QPushButton{background-color:green;\
                              color: white;   border-radius: 5px;  border: 2px groove gray;\
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




Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

//    mybutton = new switch_button(this);
//    mybutton->setText("灯光开","灯光关");
//    mybutton->show();
//    mybutton->setButtonStyle(switch_button::ButtonStyle_CircleIn);
//    mybutton->move(700,180);
      steering_mode_btn_grp =  new QButtonGroup(this);

      steering_mode_btn_grp->setExclusive(true);
      steering_mode_btn_grp->addButton(ui->steering_ecu_mode_radio_btn);
      steering_mode_btn_grp->addButton(ui->steering_auto_mode_radio_Btn);
      steering_mode_btn_grp->addButton(ui->steering_standy_mode_radio_btn);
      steering_mode_btn_grp->addButton(ui->steering_auto_test_mode_radio_btn);
      steering_mode_btn_grp->addButton(ui->steering_manu_recovery_mode_radio_btn);
     ui->steering_standy_mode_radio_btn->setChecked(true);
      connect(steering_mode_btn_grp,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(DrivingModeChange(QAbstractButton*)));

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


 // connect(ui->horntest,&QPushButton::clicked,this,&Widget::on_horn_test_click);

   ui->trunning_angle_slider->setRange(-2666,2666);
   ui->trunning_speed_slider->setRange(0,35);
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

   ui->turning_ctl_clear->setStyleSheet(mode_deselect);
   ui->turning_ctl_manu->setStyleSheet(mode_deselect);
   ui->turning_ctl_mode_btn->setStyleSheet(mode_deselect);
   ui->turning_trl_auto->setStyleSheet(mode_deselect);
   ui->turin_ctl_eps->setStyleSheet(mode_select);


   ui->accel_auto_mode->setStyleSheet(mode_deselect);
   ui->accel_clear->setStyleSheet(mode_deselect);
   ui->accel_ecu_mode->setStyleSheet(mode_select);
   ui->accel_manu_mode->setStyleSheet(mode_deselect);
   ui->accel_mode_crl->setStyleSheet(mode_deselect);


   ui->gear_auto_mode->setStyleSheet(mode_deselect);
   ui->gear_clear_mode->setStyleSheet(mode_deselect);
   ui->gear_crl_mode->setStyleSheet(mode_select);
   ui->gear_manu_mode->setStyleSheet(mode_deselect);
   ui->gear_standby_mode->setStyleSheet(mode_deselect);


   ui->parking_auto_mode->setStyleSheet(mode_deselect);
   ui->parking_clear->setStyleSheet(mode_deselect);
   ui->parking_crl_mode->setStyleSheet(mode_select);
   ui->parking_manu_mode->setStyleSheet(mode_deselect);
   ui->parking_standby_mode->setStyleSheet(mode_deselect);

   ui->light_auto_mode->setStyleSheet(mode_deselect);
   ui->light_standby_mode->setStyleSheet(mode_deselect);
   ui->light_clear->setStyleSheet(mode_deselect);
   ui->light_ctl_mode->setStyleSheet(mode_select);
   ui->light_manu_mode->setStyleSheet(mode_deselect);

   ui->brake_auto_mode->setStyleSheet(mode_deselect);
   ui->brake_clear_mode->setStyleSheet(mode_deselect);
   ui->brake_ebs_mode->setStyleSheet(mode_select);
   ui->brake_manu_mode->setStyleSheet(mode_deselect);
   ui->brake_standby_mode->setStyleSheet(mode_deselect);


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

   ui->set_open_front_fog_light->setText(tr("打开前雾灯"));
   ui->set_open_front_fog_light->setStyleSheet(open_button_style);

   ui->set_open_rear_fog_light->setText(tr("打开后雾灯"));
   ui->set_open_rear_fog_light->setStyleSheet(open_button_style);

   ui->set_close_all_lights->setText(tr("关闭所有灯光"));
   ui->set_close_all_lights->setStyleSheet(close_button_style);

   ui->set_open_parking->setText(tr("打开驻车"));
   ui->set_open_parking->setStyleSheet(open_button_style);

   ui->set_gear_forward->setStyleSheet(close_button_style);
   ui->set_gear_low->setStyleSheet(close_button_style);
   ui->set_gear_neutral->setStyleSheet(close_button_style);
   ui->set_grear_parking->setStyleSheet(close_button_style);
   ui->set_grear_reverse->setStyleSheet(close_button_style);
   ui->gear_clear->setStyleSheet(close_button_style);

   ui->label_6->openExternalLinks();
   ui->label_5->setStyleSheet("color:red;font: 12pt Arial;");

   ui->set_all_clear_manu_error->setStyleSheet(set_button_style);
   ui->set_all_ennter_auto->setStyleSheet(set_button_style);
   ui->set_all_enter_mode2->setStyleSheet(set_button_style);

   ui->steering_cali_cmd->setStyleSheet(set_button_style);
     ui->encoder_o_zero->setEnabled(false);
     ui->error_coder->setEnabled(false);
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
    ui->set_open_front_fog_light->setEnabled(enable);
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

   ui->turning_ctl_clear->setEnabled(enable);
   ui->turning_ctl_manu->setEnabled(enable);
   ui->turning_ctl_mode_btn->setEnabled(enable);
   ui->turning_trl_auto->setEnabled(enable);
   ui->turin_ctl_eps->setEnabled(enable);


   ui->accel_auto_mode->setEnabled(enable);
   ui->accel_clear->setEnabled(enable);
   ui->accel_ecu_mode->setEnabled(enable);
   ui->accel_manu_mode->setEnabled(enable);
   ui->accel_mode_crl->setEnabled(enable);


   ui->gear_auto_mode->setEnabled(enable);
   ui->gear_clear_mode->setEnabled(enable);
   ui->gear_crl_mode->setEnabled(enable);
   ui->gear_manu_mode->setEnabled(enable);
   ui->gear_standby_mode->setEnabled(enable);


   ui->parking_auto_mode->setEnabled(enable);
   ui->parking_clear->setEnabled(enable);
   ui->parking_crl_mode->setEnabled(enable);
   ui->parking_manu_mode->setEnabled(enable);
   ui->parking_standby_mode->setEnabled(enable);

   ui->light_auto_mode->setEnabled(enable);
   ui->light_standby_mode->setEnabled(enable);
   ui->light_clear->setEnabled(enable);
   ui->light_ctl_mode->setEnabled(enable);
   ui->light_manu_mode->setEnabled(enable);

   ui->brake_auto_mode->setEnabled(enable);
   ui->brake_clear_mode->setEnabled(enable);
   ui->brake_ebs_mode->setEnabled(enable);
   ui->brake_manu_mode->setEnabled(enable);
   ui->brake_standby_mode->setEnabled(enable);

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

}

void Widget::Init_UI()
{
//    switch(transmission->feedbackdata.accel_mode)
//    {
//        case 0:
//          break;
//        case 1:
//            break;
//        case 2:
//            break;
//        case 3:
//            break;
//        case 4:
//            break;

//    }

}

void Widget::set_steering_mode_style_sheet(QString stye1, QString stye2, QString stye3, QString stye4, QString stye5)
{
    ui->turning_ctl_mode_btn->setStyleSheet(stye1);
    ui->turning_trl_auto->setStyleSheet(stye2);
    ui->turin_ctl_eps->setStyleSheet(stye3);
    ui->turning_ctl_manu->setStyleSheet(stye4);
    ui->turning_ctl_clear->setStyleSheet(stye5);
}

void Widget::set_accel_mode_style_sheet(QString stye1, QString stye2, QString stye3, QString stye4, QString stye5)
{
    ui->accel_auto_mode->setStyleSheet(stye2);
    ui->accel_clear->setStyleSheet(stye5);
    ui->accel_ecu_mode->setStyleSheet(stye3);
    ui->accel_manu_mode->setStyleSheet(stye4);
    ui->accel_mode_crl->setStyleSheet(stye1);
}

void Widget::set_brake_mode_style_sheet(QString stye1, QString stye2, QString stye3, QString stye4, QString stye5)
{
    ui->brake_auto_mode->setStyleSheet(stye2);
    ui->brake_clear_mode->setStyleSheet(stye5);
    ui->brake_ebs_mode->setStyleSheet(stye3);
    ui->brake_manu_mode->setStyleSheet(stye4);
    ui->brake_standby_mode->setStyleSheet(stye1);
}

void Widget::set_gear_mode_style_sheet(QString stye1, QString stye2, QString stye3, QString stye4, QString stye5)
{
    ui->gear_auto_mode->setStyleSheet(stye2);
    ui->gear_clear_mode->setStyleSheet(stye5);
    ui->gear_crl_mode->setStyleSheet(stye3);
    ui->gear_manu_mode->setStyleSheet(stye4);
    ui->gear_standby_mode->setStyleSheet(stye1);

}

void Widget::set_light_mode_style_sheet(QString stye1, QString stye2, QString stye3, QString stye4, QString stye5)
{
    ui->light_auto_mode->setStyleSheet(stye2);
    ui->light_standby_mode->setStyleSheet(stye1);
    ui->light_clear->setStyleSheet(stye5);
    ui->light_ctl_mode->setStyleSheet(stye3);
    ui->light_manu_mode->setStyleSheet(stye4);
}

void Widget::set_parking_mode_style_sheet(QString stye1, QString stye2, QString stye3, QString stye4, QString stye5)
{
    ui->parking_auto_mode->setStyleSheet(stye2);
    ui->parking_clear->setStyleSheet(stye5);
    ui->parking_crl_mode->setStyleSheet(stye3);
    ui->parking_manu_mode->setStyleSheet(stye4);
    ui->parking_standby_mode->setStyleSheet(stye1);
}

void Widget::Dispaly_FeedBack()
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
    ui->error_coder->setText(QString::number((quint16)transmission->feedbackdata.error_code));
}

void Widget::on_turning_ctl_mode_btn_clicked()
{
    ui->turning_ctl_clear->setStyleSheet(mode_deselect);
    ui->turning_ctl_manu->setStyleSheet(mode_deselect);
    ui->turning_ctl_mode_btn->setStyleSheet(mode_select);
    ui->turning_trl_auto->setStyleSheet(mode_deselect);
    ui->turin_ctl_eps->setStyleSheet(mode_deselect);

     transmission->Send_cmd(0x11,0);
}

void Widget::on_turning_trl_auto_clicked()
{
    ui->turning_ctl_clear->setStyleSheet(mode_deselect);
    ui->turning_ctl_manu->setStyleSheet(mode_deselect);
    ui->turning_ctl_mode_btn->setStyleSheet(mode_deselect);
    ui->turning_trl_auto->setStyleSheet(mode_select);
    ui->turin_ctl_eps->setStyleSheet(mode_deselect);
    transmission->Send_cmd(0x11,1);
}

void Widget::on_turin_ctl_eps_clicked()
{
    ui->turning_ctl_clear->setStyleSheet(mode_deselect);
    ui->turning_ctl_manu->setStyleSheet(mode_deselect);
    ui->turning_ctl_mode_btn->setStyleSheet(mode_deselect);
    ui->turning_trl_auto->setStyleSheet(mode_deselect);
    ui->turin_ctl_eps->setStyleSheet(mode_select);
   transmission->Send_cmd(0x11,2);
}

void Widget::on_turning_ctl_manu_clicked()
{
    ui->turning_ctl_clear->setStyleSheet(mode_deselect);
    ui->turning_ctl_manu->setStyleSheet(mode_select);
    ui->turning_ctl_mode_btn->setStyleSheet(mode_deselect);
    ui->turning_trl_auto->setStyleSheet(mode_deselect);
    ui->turin_ctl_eps->setStyleSheet(mode_deselect);
    transmission->Send_cmd(0x11,3);

}

void Widget::on_turning_ctl_clear_clicked()
{
    ui->turning_ctl_clear->setStyleSheet(mode_select);
    ui->turning_ctl_manu->setStyleSheet(mode_deselect);
    ui->turning_ctl_mode_btn->setStyleSheet(mode_deselect);
    ui->turning_trl_auto->setStyleSheet(mode_deselect);
    ui->turin_ctl_eps->setStyleSheet(mode_deselect);
    transmission->Send_cmd(0x11,4);
}

void Widget::on_accel_mode_crl_clicked()
{
    ui->accel_auto_mode->setStyleSheet(mode_deselect);
    ui->accel_clear->setStyleSheet(mode_deselect);
    ui->accel_ecu_mode->setStyleSheet(mode_deselect);
    ui->accel_manu_mode->setStyleSheet(mode_deselect);
    ui->accel_mode_crl->setStyleSheet(mode_select);
    transmission->Send_cmd(0x21,0);
}

void Widget::on_accel_auto_mode_clicked()
{
    ui->accel_auto_mode->setStyleSheet(mode_select);
    ui->accel_clear->setStyleSheet(mode_deselect);
    ui->accel_ecu_mode->setStyleSheet(mode_deselect);
    ui->accel_manu_mode->setStyleSheet(mode_deselect);
    ui->accel_mode_crl->setStyleSheet(mode_deselect);
    transmission->Send_cmd(0x21,1);
}

void Widget::on_accel_ecu_mode_clicked()
{
    ui->accel_auto_mode->setStyleSheet(mode_deselect);
    ui->accel_clear->setStyleSheet(mode_deselect);
    ui->accel_ecu_mode->setStyleSheet(mode_select);
    ui->accel_manu_mode->setStyleSheet(mode_deselect);
    ui->accel_mode_crl->setStyleSheet(mode_deselect);

  transmission->Send_cmd(0x21,2);
}

void Widget::on_accel_manu_mode_clicked()
{
    ui->accel_auto_mode->setStyleSheet(mode_deselect);
    ui->accel_clear->setStyleSheet(mode_deselect);
    ui->accel_ecu_mode->setStyleSheet(mode_deselect);
    ui->accel_manu_mode->setStyleSheet(mode_select);
    ui->accel_mode_crl->setStyleSheet(mode_deselect);

  transmission->Send_cmd(0x21,3);
}

void Widget::on_accel_clear_clicked()
{
    ui->accel_auto_mode->setStyleSheet(mode_deselect);
    ui->accel_clear->setStyleSheet(mode_select);
    ui->accel_ecu_mode->setStyleSheet(mode_deselect);
    ui->accel_manu_mode->setStyleSheet(mode_deselect);
    ui->accel_mode_crl->setStyleSheet(mode_deselect);

  transmission->Send_cmd(0x21,4);
}

void Widget::on_brake_standby_mode_clicked()
{
    ui->brake_auto_mode->setStyleSheet(mode_deselect);
    ui->brake_clear_mode->setStyleSheet(mode_deselect);
    ui->brake_ebs_mode->setStyleSheet(mode_deselect);
    ui->brake_manu_mode->setStyleSheet(mode_deselect);
    ui->brake_standby_mode->setStyleSheet(mode_select);
    transmission->Send_cmd(0x31,0);
}

void Widget::on_brake_auto_mode_clicked()
{
    ui->brake_auto_mode->setStyleSheet(mode_select);
    ui->brake_clear_mode->setStyleSheet(mode_deselect);
    ui->brake_ebs_mode->setStyleSheet(mode_deselect);
    ui->brake_manu_mode->setStyleSheet(mode_deselect);
    ui->brake_standby_mode->setStyleSheet(mode_deselect);

    transmission->Send_cmd(0x31,1);
}

void Widget::on_brake_ebs_mode_clicked()
{
    ui->brake_auto_mode->setStyleSheet(mode_deselect);
    ui->brake_clear_mode->setStyleSheet(mode_deselect);
    ui->brake_ebs_mode->setStyleSheet(mode_select);
    ui->brake_manu_mode->setStyleSheet(mode_deselect);
    ui->brake_standby_mode->setStyleSheet(mode_deselect);
     transmission->Send_cmd(0x31,2);
}

void Widget::on_brake_manu_mode_clicked()
{
    ui->brake_auto_mode->setStyleSheet(mode_deselect);
    ui->brake_clear_mode->setStyleSheet(mode_deselect);
    ui->brake_ebs_mode->setStyleSheet(mode_deselect);
    ui->brake_manu_mode->setStyleSheet(mode_select);
    ui->brake_standby_mode->setStyleSheet(mode_deselect);
    transmission->Send_cmd(0x31,3);
}

void Widget::on_brake_clear_mode_clicked()
{
    ui->brake_auto_mode->setStyleSheet(mode_deselect);
    ui->brake_clear_mode->setStyleSheet(mode_select);
    ui->brake_ebs_mode->setStyleSheet(mode_deselect);
    ui->brake_manu_mode->setStyleSheet(mode_deselect);
    ui->brake_standby_mode->setStyleSheet(mode_deselect);
    transmission->Send_cmd(0x31,4);
}

void Widget::on_gear_standby_mode_clicked()
{
    ui->gear_auto_mode->setStyleSheet(mode_deselect);
    ui->gear_clear_mode->setStyleSheet(mode_deselect);
    ui->gear_crl_mode->setStyleSheet(mode_deselect);
    ui->gear_manu_mode->setStyleSheet(mode_deselect);
    ui->gear_standby_mode->setStyleSheet(mode_select);
    transmission->Send_cmd(0x41,0);
}

void Widget::on_gear_auto_mode_clicked()
{
    ui->gear_auto_mode->setStyleSheet(mode_select);
    ui->gear_clear_mode->setStyleSheet(mode_deselect);
    ui->gear_crl_mode->setStyleSheet(mode_deselect);
    ui->gear_manu_mode->setStyleSheet(mode_deselect);
    ui->gear_standby_mode->setStyleSheet(mode_deselect);
    transmission->Send_cmd(0x41,1);
}

void Widget::on_gear_crl_mode_clicked()
{
    ui->gear_auto_mode->setStyleSheet(mode_deselect);
    ui->gear_clear_mode->setStyleSheet(mode_deselect);
    ui->gear_crl_mode->setStyleSheet(mode_select);
    ui->gear_manu_mode->setStyleSheet(mode_deselect);
    ui->gear_standby_mode->setStyleSheet(mode_deselect);
     transmission->Send_cmd(0x41,2);
}

void Widget::on_gear_manu_mode_clicked()
{
    ui->gear_auto_mode->setStyleSheet(mode_deselect);
    ui->gear_clear_mode->setStyleSheet(mode_deselect);
    ui->gear_crl_mode->setStyleSheet(mode_deselect);
    ui->gear_manu_mode->setStyleSheet(mode_select);
    ui->gear_standby_mode->setStyleSheet(mode_deselect);
  transmission->Send_cmd(0x41,3);
}

void Widget::on_gear_clear_mode_clicked()
{
    ui->gear_auto_mode->setStyleSheet(mode_deselect);
    ui->gear_clear_mode->setStyleSheet(mode_select);
    ui->gear_crl_mode->setStyleSheet(mode_deselect);
    ui->gear_manu_mode->setStyleSheet(mode_deselect);
    ui->gear_standby_mode->setStyleSheet(mode_deselect);


    transmission->Send_cmd(0x41,4);
}

void Widget::on_light_standby_mode_clicked()
{
    ui->light_standby_mode->setStyleSheet(mode_select);
    ui->light_clear->setStyleSheet(mode_deselect);
    ui->light_ctl_mode->setStyleSheet(mode_deselect);
    ui->light_manu_mode->setStyleSheet(mode_deselect);
    ui->light_auto_mode->setStyleSheet(mode_deselect);
    transmission->Send_cmd(0x61,0);
}

void Widget::on_light_auto_mode_clicked()
{
    ui->light_auto_mode->setStyleSheet(mode_select);
    ui->light_standby_mode->setStyleSheet(mode_deselect);
    ui->light_clear->setStyleSheet(mode_deselect);
    ui->light_ctl_mode->setStyleSheet(mode_deselect);
    ui->light_manu_mode->setStyleSheet(mode_deselect);
  transmission->Send_cmd(0x61,1);
}

void Widget::on_light_ctl_mode_clicked()
{
    ui->light_auto_mode->setStyleSheet(mode_deselect);
    ui->light_standby_mode->setStyleSheet(mode_deselect);
    ui->light_clear->setStyleSheet(mode_deselect);
    ui->light_ctl_mode->setStyleSheet(mode_select);
    ui->light_manu_mode->setStyleSheet(mode_deselect);
     transmission->Send_cmd(0x61,2);
}

void Widget::on_light_manu_mode_clicked()
{
    ui->light_auto_mode->setStyleSheet(mode_deselect);
    ui->light_standby_mode->setStyleSheet(mode_deselect);
    ui->light_clear->setStyleSheet(mode_deselect);
    ui->light_ctl_mode->setStyleSheet(mode_deselect);
    ui->light_manu_mode->setStyleSheet(mode_select);
     transmission->Send_cmd(0x61,3);
}

void Widget::on_light_clear_clicked()
{
    ui->light_auto_mode->setStyleSheet(mode_deselect);
    ui->light_standby_mode->setStyleSheet(mode_deselect);
    ui->light_clear->setStyleSheet(mode_select);
    ui->light_ctl_mode->setStyleSheet(mode_deselect);
    ui->light_manu_mode->setStyleSheet(mode_deselect);

}

void Widget::on_parking_standby_mode_clicked()
{
    ui->parking_auto_mode->setStyleSheet(mode_deselect);
    ui->parking_clear->setStyleSheet(mode_deselect);
    ui->parking_crl_mode->setStyleSheet(mode_deselect);
    ui->parking_manu_mode->setStyleSheet(mode_deselect);
    ui->parking_standby_mode->setStyleSheet(mode_select);
     transmission->Send_cmd(0x51,0);
}

void Widget::on_parking_auto_mode_clicked()
{
    ui->parking_auto_mode->setStyleSheet(mode_select);
    ui->parking_clear->setStyleSheet(mode_deselect);
    ui->parking_crl_mode->setStyleSheet(mode_deselect);
    ui->parking_manu_mode->setStyleSheet(mode_deselect);
    ui->parking_standby_mode->setStyleSheet(mode_deselect);

    transmission->Send_cmd(0x51,1);
}

void Widget::on_parking_crl_mode_clicked()
{
    ui->parking_auto_mode->setStyleSheet(mode_deselect);
    ui->parking_clear->setStyleSheet(mode_deselect);
    ui->parking_crl_mode->setStyleSheet(mode_select);
    ui->parking_manu_mode->setStyleSheet(mode_deselect);
    ui->parking_standby_mode->setStyleSheet(mode_deselect);
    transmission->Send_cmd(0x51,2);
}

void Widget::on_parking_manu_mode_clicked()
{
    ui->parking_auto_mode->setStyleSheet(mode_deselect);
    ui->parking_clear->setStyleSheet(mode_deselect);
    ui->parking_crl_mode->setStyleSheet(mode_deselect);
    ui->parking_manu_mode->setStyleSheet(mode_select);
    ui->parking_standby_mode->setStyleSheet(mode_deselect);
    transmission->Send_cmd(0x51,3);
}

void Widget::on_parking_clear_clicked()
{
    ui->parking_auto_mode->setStyleSheet(mode_deselect);
    ui->parking_clear->setStyleSheet(mode_select);
    ui->parking_crl_mode->setStyleSheet(mode_deselect);
    ui->parking_manu_mode->setStyleSheet(mode_deselect);
    ui->parking_standby_mode->setStyleSheet(mode_deselect);

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
    ui->set_gear_forward->setStyleSheet(close_button_style);
    ui->set_gear_low->setStyleSheet(close_button_style);
    ui->set_gear_neutral->setStyleSheet(close_button_style);
    ui->set_grear_parking->setStyleSheet(open_button_style);
    ui->set_grear_reverse->setStyleSheet(close_button_style);
    transmission->Send_cmd(0x42,1);
}

void Widget::on_set_grear_reverse_clicked()
{
    ui->set_gear_forward->setStyleSheet(close_button_style);
    ui->set_gear_low->setStyleSheet(close_button_style);
    ui->set_gear_neutral->setStyleSheet(close_button_style);
    ui->set_grear_parking->setStyleSheet(close_button_style);
    ui->set_grear_reverse->setStyleSheet(open_button_style);
    transmission->Send_cmd(0x42,2);
}

void Widget::on_set_gear_neutral_clicked()
{
    ui->set_gear_forward->setStyleSheet(close_button_style);
    ui->set_gear_low->setStyleSheet(close_button_style);
    ui->set_gear_neutral->setStyleSheet(open_button_style);
    ui->set_grear_parking->setStyleSheet(close_button_style);
    ui->set_grear_reverse->setStyleSheet(close_button_style);
    transmission->Send_cmd(0x42,3);
}

void Widget::on_set_gear_forward_clicked()
{
    ui->set_gear_forward->setStyleSheet(open_button_style);
    ui->set_gear_low->setStyleSheet(close_button_style);
    ui->set_gear_neutral->setStyleSheet(close_button_style);
    ui->set_grear_parking->setStyleSheet(close_button_style);
    ui->set_grear_reverse->setStyleSheet(close_button_style);
    transmission->Send_cmd(0x42,4);
}

void Widget::on_set_gear_low_clicked()
{
    ui->set_gear_forward->setStyleSheet(close_button_style);
    ui->set_gear_low->setStyleSheet(open_button_style);
    ui->set_gear_neutral->setStyleSheet(close_button_style);
    ui->set_grear_parking->setStyleSheet(close_button_style);
    ui->set_grear_reverse->setStyleSheet(close_button_style);
    transmission->Send_cmd(0x42,5);
}

void Widget::on_gear_clear_clicked()
{
    ui->set_gear_forward->setStyleSheet(close_button_style);
    ui->set_gear_low->setStyleSheet(close_button_style);
    ui->set_gear_neutral->setStyleSheet(close_button_style);
    ui->set_grear_parking->setStyleSheet(close_button_style);
    ui->set_grear_reverse->setStyleSheet(close_button_style);
    ui->gear_clear->setStyleSheet(close_button_style);
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
    if(ui->set_open_front_fog_light->text() == tr("打开前雾灯"))
     {
           light_crl_bits |= (1<<5);
           ui->set_open_front_fog_light->setText(tr("关闭前雾灯"));
           ui->set_open_front_fog_light->setStyleSheet(close_button_style);
     }
    else
    {
        light_crl_bits &= ~(1<<5);
        ui->set_open_front_fog_light->setText(tr("打开前雾灯"));
        ui->set_open_front_fog_light->setStyleSheet(open_button_style);
    }
     qDebug() << "Light_crt_bits="<<light_crl_bits;
    transmission->Send_cmd(0x62,light_crl_bits);
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

    ui->set_open_front_fog_light->setText(tr("打开前雾灯"));
    ui->set_open_front_fog_light->setStyleSheet(open_button_style);

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
    set_steering_mode_style_sheet(mode_deselect,mode_select,mode_deselect,mode_deselect,mode_deselect);
    set_accel_mode_style_sheet(mode_deselect,mode_select,mode_deselect,mode_deselect,mode_deselect);
    set_brake_mode_style_sheet(mode_deselect,mode_select,mode_deselect,mode_deselect,mode_deselect);
    set_gear_mode_style_sheet(mode_deselect,mode_select,mode_deselect,mode_deselect,mode_deselect);
    set_light_mode_style_sheet(mode_deselect,mode_select,mode_deselect,mode_deselect,mode_deselect);
    set_parking_mode_style_sheet(mode_deselect,mode_select,mode_deselect,mode_deselect,mode_deselect);

    transmission->Send_cmd(0x61,4);

}

void Widget::on_set_all_clear_manu_error_clicked()
{
   set_steering_mode_style_sheet(mode_deselect,mode_deselect,mode_deselect,mode_select,mode_deselect);
   set_accel_mode_style_sheet(mode_deselect,mode_deselect,mode_deselect,mode_select,mode_deselect);
   set_brake_mode_style_sheet(mode_deselect,mode_deselect,mode_deselect,mode_select,mode_deselect);
   set_gear_mode_style_sheet(mode_deselect,mode_deselect,mode_deselect,mode_select,mode_deselect);
   set_light_mode_style_sheet(mode_deselect,mode_deselect,mode_deselect,mode_select,mode_deselect);
   set_parking_mode_style_sheet(mode_deselect,mode_deselect,mode_deselect,mode_select,mode_deselect);
    transmission->Send_cmd(0x51,4);
}

void Widget::on_set_all_enter_mode2_clicked()
{
    set_steering_mode_style_sheet(mode_deselect,mode_deselect,mode_select,mode_deselect,mode_deselect);
    set_accel_mode_style_sheet(mode_deselect,mode_deselect,mode_select,mode_deselect,mode_deselect);
    set_brake_mode_style_sheet(mode_deselect,mode_deselect,mode_select,mode_deselect,mode_deselect);
    set_gear_mode_style_sheet(mode_deselect,mode_deselect,mode_select,mode_deselect,mode_deselect);
    set_light_mode_style_sheet(mode_deselect,mode_deselect,mode_select,mode_deselect,mode_deselect);
    set_parking_mode_style_sheet(mode_deselect,mode_deselect,mode_select,mode_deselect,mode_deselect);
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
}


void Widget::DrivingModeChange(QAbstractButton* btn)
{
    // 遍历按钮，获取选中状态
     QList<QAbstractButton*> list = steering_mode_btn_grp->buttons();
     foreach (QAbstractButton *pButton, list)
     {
         QString strStatus = pButton->isChecked() ? "Checked" : "Unchecked";
         qDebug() << QString("Button : %1 is %2").arg(pButton->text()).arg(strStatus);
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

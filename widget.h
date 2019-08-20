#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QList>
#include <QQueue>
#include <stdlib.h>
#include <qformlayout.h>
#include "mytransmission.h"
#include <qstylefactory.h>
#include "switch_button.h"
#include "QButtonGroup"

class switch_button;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    myTransmission *transmission;
    QTimer *timer;
    QTimer *timer1;
    QTimer *check_connect_timer;
    uint16_t light_crl_bits = 0;

    int16_t steering_angle = 0;
    int16_t steering_speed = 0;
    int16_t accel_val = 0;
    int16_t brake_val = 0;
    switch_button *mybutton;

    QButtonGroup *steering_mode_btn_grp;
    QButtonGroup *driving_mode_btn_grp;
    QButtonGroup *braking_mode_btn_grp;
    QButtonGroup *gear_mode_btn_grp;
    QButtonGroup *lighting_mode_btn_grp;
    QButtonGroup *parking_mode_btn_grp;

    int  ScanfSerialPort();
    void enable_button(bool enable);
    void Init_UI();

    void set_steering_mode_style_sheet(QString stye1,QString stye2,QString stye3,QString stye4,QString stye5);
    void set_accel_mode_style_sheet(QString stye1,QString stye2,QString stye3,QString stye4,QString stye5);
    void set_brake_mode_style_sheet(QString stye1,QString stye2,QString stye3,QString stye4,QString stye5);
    void set_gear_mode_style_sheet(QString stye1,QString stye2,QString stye3,QString stye4,QString stye5);
    void set_light_mode_style_sheet(QString stye1,QString stye2,QString stye3,QString stye4,QString stye5);
    void set_parking_mode_style_sheet(QString stye1,QString stye2,QString stye3,QString stye4,QString stye5);
private slots:

    void Dispaly_FeedBack();

    void on_turning_ctl_mode_btn_clicked();
    void on_turning_trl_auto_clicked();
    void on_turin_ctl_eps_clicked();
    void on_turning_ctl_manu_clicked();
    void on_turning_ctl_clear_clicked();
    void on_accel_mode_crl_clicked();
    void on_accel_auto_mode_clicked();
    void on_accel_ecu_mode_clicked();
    void on_accel_manu_mode_clicked();
    void on_accel_clear_clicked();
    void on_brake_standby_mode_clicked();
    void on_brake_auto_mode_clicked();
    void on_brake_ebs_mode_clicked();
    void on_brake_manu_mode_clicked();
    void on_brake_clear_mode_clicked();
    void on_gear_standby_mode_clicked();
    void on_gear_auto_mode_clicked();
    void on_gear_crl_mode_clicked();
    void on_gear_manu_mode_clicked();
    void on_gear_clear_mode_clicked();
    void on_light_standby_mode_clicked();
    void on_light_auto_mode_clicked();
    void on_light_ctl_mode_clicked();
    void on_light_manu_mode_clicked();
    void on_light_clear_clicked();
    void on_parking_standby_mode_clicked();
    void on_parking_auto_mode_clicked();
    void on_parking_crl_mode_clicked();
    void on_parking_manu_mode_clicked();
    void on_parking_clear_clicked();
    void on_StartOrStopButton_5_clicked();
    void on_set_grear_parking_clicked();
    void on_set_grear_reverse_clicked();
    void on_set_gear_neutral_clicked();
    void on_set_gear_forward_clicked();
    void on_set_gear_low_clicked();
    void on_gear_clear_clicked();
    void on_set_open_left_light_clicked();
    void on_set_open_low_beam_light_clicked();
    void on_set_open_front_fog_light_clicked();
    void on_set_open_warning_light_clicked();
    void on_set_open_right_light_clicked();
    void on_set_open_hight_beam_light_clicked();
    void on_set_open_rear_fog_light_clicked();
    void on_set_close_all_lights_clicked();
    void on_set_open_parking_clicked();

    void OnSteeringAngleSub100Click();
    void OnSteeringAngleSub1Click();
    void OnSteeringSpeedSub100Click();
    void OnSteeringSpeedSub1Click();

    void OnSteeringAngleAdd100Click();
    void OnSteeringAngleAdd1Click();
    void OnSteeringSpeedAdd100Click();
    void OnSteeringSpeedAdd1Click();
    void OnSteeringCaliCmdClick();



    void OnAccelSub10Click();
    void OnAccelSub1Click();
    void OnAccelAdd10Click();
    void OnAccelADD1Click();

    void OnBrakesub10Click();
    void OnBrakeSub1Click();
    void OnBrakeAdd10Click();
    void OnBrakeADD1Click();

    void SlideChangeSteeringAngle(int value);
    void SlideChangeSteeringSpeed(int value);
    void SlideChangeAccel(int value);
    void SlideChangeBrake(int value);

    void LineEditChangeSteeringAngle();
    void LineEditChangeSteeringSpeed();
    void LineEditChangeAccel();
    void SLineEditChangeBrake();
    void CheckConnectStatus();

    void on_set_all_ennter_auto_clicked();
    void on_set_all_clear_manu_error_clicked();
    void on_set_all_enter_mode2_clicked();

    void DrivingModeChange(QAbstractButton*);
    void on_horntest_clicked();
};

#endif // WIDGET_H

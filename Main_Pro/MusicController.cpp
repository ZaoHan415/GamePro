 #include "MusicController.h"

MusicController::MusicController(QWidget *parent)
    :QDialog (parent)
{
    ui.setupUi(this);
    ui.BGMSlider->setMinimum(0);
    ui.BGMSlider->setMaximum(100);
    ui.BGMSlider->setValue(50);//滑块预设50
    ui.ISSlider->setMaximum(0);
    ui.ISSlider->setMaximum(100);
    ui.ISSlider->setValue(50);//滑块预设50

    connect(ui.OKbtn,SIGNAL(clicked()),this,SLOT(onSureMusic()));
    connect(ui.BGMSlider,SIGNAL(valueChanged(int)),this,SLOT(setBackgroundValue(int)));
    connect(ui.ISSlider, SIGNAL(valueChanged(int)), this, SLOT(setISsound(int)));
}
MusicController::~MusicController()
{

}
void MusicController::onSureMusic()
{
    accept();
}
void MusicController::setBackgroundValue(int )
{
    int pos = ui.BGMSlider->value();//获取Slider的数值
    QString str = QString::number(pos);//将其化为字符串
    ui.bgmPos->setText(str);//修改到QLabel
    bgmVolume = pos;
}
void MusicController::setISsound(int )
{
    int pos = ui.ISSlider->value();//获取Slider的值
    QString str = QString::number(pos);//将其化为字符串
    ui.isPos->setText(str);
    isvolume = pos;//修改到QLabel
}





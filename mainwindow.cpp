#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->about->setText("Vogen采样歌词处理工具 版本"+VL_Version+"\n暂不支持多音字，需手动修改");
    ui->Buttom->setText("Vogen采样歌词处理工具 版本"+VL_Version+"\n©2021 無常.保留所有权利.\nQt版本："+QString(qVersion())+" 编译时间："+QString(__DATE__)+" "+QString(__TIME__));
    this->solveDictionaryList();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_aboutQt_clicked()
{
    QMessageBox::aboutQt(this,"关于Qt");
}

void MainWindow::solveDictionaryList()
{
    QFile listfile(":/source/dics.txt");
    if(listfile.open(QIODevice::ReadOnly|QIODevice::Text)){
        QStringList fplist=QString(listfile.readAll()).split("\n",Qt::SkipEmptyParts);
        listfile.close();

        for(int i=0;i<fplist.size();i++){
            QString dirpath=":/dics/"+fplist.at(i);
            QFile inforfile(dirpath+"/dictionary.json"),charfile(dirpath+"/character.raw"),tranfile(dirpath+"/translate.raw");
            if(inforfile.exists()&&charfile.exists()&&tranfile.exists()){
                if(inforfile.open(QIODevice::ReadOnly|QIODevice::Text)){
                    QJsonDocument jd=QJsonDocument::fromJson((inforfile.readAll()));
                    inforfile.close();
                    if(jd.isObject()){
                        QJsonObject jo=jd.object();
                        if(jo["version"].toDouble()<=D_Version){
                            if(tranfile.open(QIODevice::ReadOnly|QIODevice::Text)){
                                ui->dics->addItem(jo["name"].toString());
                                QString trandata=tranfile.readAll();
                                tranfile.close();

                                QHash<QString,QString> maph;
                                QStringList tranlist=trandata.split("\n",Qt::SkipEmptyParts);
                                for(int j=0;j<tranlist.size();j++){
                                    QStringList sublist=tranlist.at(j).split(" ",Qt::SkipEmptyParts);
                                    if(sublist.size()==2){
                                        maph.insert(sublist.at(0),sublist.at(1));
                                    }
                                }

                                this->tranl.insert(jo["name"].toString(),maph);
                            }
                        }
                    }
                }
            }
        }
    }
}

void MainWindow::on_source_textChanged()
{
    solvetran();
}

void MainWindow::solvetran()
{
    QHash<QString,QString> mapt=this->tranl[ui->dics->currentText()];
    QString stext=ui->source->toPlainText();
    QString out;
    QStringList plainlist=stext.split("\n",Qt::SkipEmptyParts);
    for(int i=0;i<plainlist.size();i++){
        QString plainin=plainlist.at(i);
        QString plainout;
        plainin.remove(" ");
        for(int j=0;j<plainin.size();j++){
            QString chart=plainin.mid(j,1);
            if(chart!=" "){
                if(mapt.contains(chart)){
                    plainout+=chart;
                    plainout+=mapt[chart];
                }else{
                    plainout+="⊗";
                    plainout+="⊗";
                }
                if(j<plainin.size()-1){
                    plainout+=" ";
                }
            }
        }
        out+=plainout;
        if(i<plainlist.size()-1){
            out+="\n";
        }
    }
    ui->out->setPlainText(out);
}

void MainWindow::on_dics_currentTextChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    solvetran();
}


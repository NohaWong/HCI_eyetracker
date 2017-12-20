#include "mainwindow.h"



MainWindow::MainWindow() {
  glWidget_ = new GLWidget();
  file_dir_ = QDir(QDir::currentPath(), tr("*.txt"));
  file_name_ = tr("");

  QHBoxLayout* centralLayout = new QHBoxLayout;
  centralLayout->addWidget(glWidget_);
  centralLayout->addLayout(create_file_layout());
  setLayout(centralLayout);

  update_file_list();
  setWindowTitle(tr("Pointing experience with voronoi"));
  layout()->setSizeConstraint(QLayout::SetFixedSize);
}


void MainWindow::Exp_1_Clicked() {
  file_dir_.setPath(QDir::currentPath()+"/Experience_1");
  file_name_Exp_ = file_dir_.entryList(QDir::Files,QDir::Name);
  index_exp=0;
  //next_file();
  //glWidget_->Start_Exp_1();
}

void MainWindow::Exp_2_Clicked() {
  file_dir_.setPath(QDir::currentPath()+"/Experience_2");;
  file_name_Exp_ = file_dir_.entryList(QDir::Files,QDir::Name);
  index_exp=0;
  //next_file();
  //glWidget_->Start_Exp_2();
}

void MainWindow::Exp_3_Clicked() {

  file_dir_.setPath(QDir::currentPath()+"/Experience_3");
  file_name_Exp_ = file_dir_.entryList(QDir::Files,QDir::Name);
  index_exp=0;
  //next_file();
  //glWidget_->Start_Exp_3();
}


void MainWindow::browse() {
  QString new_path = QFileDialog::getExistingDirectory(
      0, tr("Choose Directory"), file_dir_.absolutePath());
  if (new_path.isEmpty()) {
    return;
  }
  file_dir_.setPath(new_path);
  update_file_list();
}

void MainWindow::build() {
  file_name_ = file_list_->currentItem()->text();
  QString file_path = file_dir_.filePath(file_name_);
  message_label_->setText("Building...");
  glWidget_->build(file_path);
  message_label_->setText("Double click the item to build voronoi diagram:");
  setWindowTitle(tr("Voronoi Visualizer - ") + file_path);
}

void MainWindow::print_scr() {
  if (!file_name_.isEmpty()) {
    QImage screenshot = glWidget_->grabFrameBuffer(true);
    QString output_file = file_dir_.absolutePath() + tr("/") +
        file_name_.left(file_name_.indexOf('.')) + tr(".png");
    screenshot.save(output_file, 0, -1);
  }
}


QGridLayout* MainWindow::create_file_layout() {
    QGridLayout* file_layout = new QGridLayout;

    message_label_ = new QLabel("Double click item to build voronoi diagram:");

    file_list_ = new QListWidget();
    file_list_->connect(file_list_,
                        SIGNAL(itemDoubleClicked(QListWidgetItem*)),
                        this,
                        SLOT(build()));


    // GroupBox to start the experiences.

    QGroupBox *groupBoxExp = new QGroupBox("Select experience");
    QRadioButton *Exp_1_radio = new QRadioButton("1er experience");
    QRadioButton *Exp_2_radio = new QRadioButton("2eme experience");
    QRadioButton *Exp_3_radio = new QRadioButton("3eme experience");

    connect(Exp_1_radio, SIGNAL(clicked()), this, SLOT(Exp_1_Clicked()));
    connect(Exp_2_radio, SIGNAL(clicked()), this, SLOT(Exp_2_Clicked()));
    connect(Exp_3_radio, SIGNAL(clicked()), this, SLOT(Exp_3_Clicked()));

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(Exp_1_radio);
    vbox->addWidget(Exp_2_radio);
    vbox->addWidget(Exp_3_radio);
    groupBoxExp->setLayout(vbox);


    QPushButton* browse_button =
        new QPushButton(tr("Browse Input Directory"));
    connect(browse_button, SIGNAL(clicked()), this, SLOT(browse()));
    browse_button->setMinimumHeight(50);

    QPushButton* print_scr_button = new QPushButton(tr("Make Screenshot"));
    connect(print_scr_button, SIGNAL(clicked()), this, SLOT(print_scr()));
    print_scr_button->setMinimumHeight(50);


    QPushButton* start_button = new QPushButton(tr("Next Test - Start"));
    connect(start_button, SIGNAL(clicked()), this, SLOT(next_file()));
    start_button->setMinimumHeight(50);

    file_layout->addWidget(message_label_, 0, 0);
    file_layout->addWidget(file_list_, 1, 0);
    file_layout->addWidget(groupBoxExp,2,0);
    //file_layout->addWidget(primary_checkbox, 2, 0);
    //file_layout->addWidget(internal_checkbox, 3, 0);
    file_layout->addWidget(start_button, 4, 0);
    file_layout->addWidget(browse_button, 5, 0);

    //file_layout->addWidget(print_scr_button, 5, 0);

    return file_layout;
}

void MainWindow::update_file_list() {
    QFileInfoList list = file_dir_.entryInfoList();
    file_list_->clear();
    if (file_dir_.count() == 0) {
        return;
    }
    QFileInfoList::const_iterator it;
    for (it = list.begin(); it != list.end(); it++) {
        file_list_->addItem(it->fileName());
    }
    file_list_->setCurrentRow(0);
}






void MainWindow::next_file(){


    if(index_exp < file_name_Exp_.size()){
         glWidget_->build(file_dir_.filePath(file_name_Exp_[0]));
        //Point p = Point(2.0,3.0);
        //glWidget_->color_a_voronoi_cell(p);
    }
    else{

        glWidget_->end_exp_=true;
    }
    //glWidget_->end_exp_=true;
    index_exp++;

}

// Voir pour les data
void MainWindow::write_data(){

}

#include <QApplication>
#include <Qt3DCore>
#include <Qt3DRender>
#include <Qt3DInput>
#include <Qt3DExtras>
#include <QString>

Qt3DCore::QEntity *createScene(QString diretorio){

    Qt3DCore::QEntity *entidadeBase = new Qt3DCore::QEntity;
    Qt3DRender::QMaterial *material = new Qt3DExtras::QPhongMaterial(entidadeBase);
    Qt3DCore::QEntity *entidadeObjeto = new Qt3DCore::QEntity(entidadeBase);
    Qt3DRender::QMesh *malhaObjeto = new Qt3DRender::QMesh(entidadeBase);
    //malhaObjeto->setSource(QUrl::fromLocalFile("/home/gustavo/CGR/TC3/TrabCGR/coffee_cup.obj"));
    malhaObjeto->setSource(QUrl::fromLocalFile(diretorio));


    entidadeObjeto->addComponent(malhaObjeto);
    entidadeObjeto->addComponent(material);

   return entidadeBase;
}
int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    Qt3DExtras::Qt3DWindow view;

    //qInfo() << QDir(".").absolutePath();
    //Qt3DCore::QEntity *scene = createScene("/home/gustavo/CGR/TC3/TrabCGR/Esponja.obj");
    //Qt3DCore::QEntity *scene = createScene(QDir(".").absolutePath() + "/Esponja.obj");
    Qt3DCore::QEntity *scene = createScene(QDir(".").absolutePath() + "/" + QString(argv[1]));

    // Camera
    Qt3DRender::QCamera *camera = view.camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 0, 40.0f));
    camera->setViewCenter(QVector3D(0, 0, 0));

    //Controles da camera
    Qt3DExtras::QOrbitCameraController *controleCamera = new Qt3DExtras::QOrbitCameraController(scene);
    controleCamera->setLinearSpeed( 50.0f );
    controleCamera->setLookSpeed( 180.0f );
    controleCamera->setCamera(camera);

    view.setRootEntity(scene);
    view.show();

    return app.exec();
}

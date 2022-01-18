#-------------------------------------------------
#
# Project created by Dukend
#
#-------------------------------------------------

QT       += core gui opengl #<===========================

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
TARGET = Kondratev306
#TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
		ruledsurfacebycardinalspline.cpp\
		glsphere.cpp\
		cardinalsplineclass.cpp\
		glwidget.cpp\
		splinesettingswidget.cpp\
		glabstractpainting.cpp\
		lightsettingswidget.cpp\
		surfacesettingswidget.cpp\
		glcuboid.cpp\
		pointfieldwidget.cpp\
		viewwidget.cpp\
		glfigureengine.cpp\
		gllight.cpp\
		main.cpp

HEADERS += \
		gllight.h\
		ruledsurfacebycardinalspline.h\
		glsphere.h\
		glwidget.h\
		cardinalsplineclass.h\
		splinesettingswidget.h\
		glabstractpainting.h\
		lightsettingswidget.h\
		surfacesettingswidget.h\
		glcuboid.h\
		pointfieldwidget.h\
		viewwidget.h\
		glfigureengine.h\
		polynom.h




# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -lopengl32 #<===========================

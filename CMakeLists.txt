cmake_minimum_required(VERSION 3.16)

project(ilbm-thumb-kde
    DESCRIPTION "ILBM file thumbnail generator for Plasma"
	)

set(QT_MIN_VERSION "5.3.0")
set(KF5_MIN_VERSION "5.2.0")

find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(FeatureSummary)

# Find Qt modules
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS 
    Core    # QCommandLineParser, QStringLiteral
    Widgets # QApplication 
)

# Find KDE modules
find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
    KIO
)

find_package(ImageMagick REQUIRED COMPONENTS Magick++)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)

set(ilbmthumbnail_SRCS ilbmcreator.cpp)

add_library(ilbmthumbnail MODULE ${ilbmthumbnail_SRCS})

set(CMAKE_STATIC_LINKER_FLAGS "-ldl -ldl -lutil -lutil -ldl -lrt -lpthread -lgcc_s -lc -lm -lrt -lpthread -lutil -lutil")

add_definitions(-fexceptions)

target_link_libraries(ilbmthumbnail
    Qt5::Widgets
    KF5::KIOWidgets
    ImageMagick::Magick++
    # Dependencies from running `cargo rustc --lib -- --print native-static-libs`
    dl
    util
    rt
    pthread
    gcc_s
    c
    m
)
target_include_directories(ilbmthumbnail PUBLIC ${ImageMagick_Magick++_INCLUDE_DIRS})
install(TARGETS ilbmthumbnail DESTINATION ${LIB_INSTALL_DIR}/qt5/plugins/)
install(FILES ilbmthumbnail.desktop DESTINATION ${SERVICES_INSTALL_DIR})

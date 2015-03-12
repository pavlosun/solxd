#ifndef CRYSTFILE_H
#define CRYSTFILE_H
#include "unitcell.h"
#include <QString>
#include <QList>
#include <QMetaType>
//#include <cctbx/uctbx/fast_minimum_reduction.h>


class Crystfile : public Unitcell
{
public:
    Crystfile();
    Crystfile(FileType type, const QString &path);
//    void setPath(const char *path){_path=path;}
/*
 * error is a percentage deviation for each unit cell parameter
 * for example, all cell within range cell(1-error) < cell < cell(1+error)
 *
*/
    bool findCell(const Unitcell &cell, const double &error);
    bool findWL(const double &wl,const double &error);
    bool findSfac(const QString &sfac);
    bool findBrave(const CellType &ctype);
    bool findCellA(const double &cellA,const double &error);
    bool findCellB(const double &cellB,const double &error);
    bool findCellC(const double &cellC,const double &error);
    bool findCellAlpha(const double &cellAlpha,const double &error);
    bool findCellBeta(const double &cellBeta,const double &error);
    bool findCellGamma(const double &cellGamma,const double &error);
    bool findVolume(const double &vol, const double &error);

    inline const QString &getPath()const {return _path;}
    inline const FileType &getFileType()const{return _type;}
    inline const CellType &getCellType()const{return _ctype;}
    inline const double &getWavelength()const{return _wavelength;}
    inline const bool &isCenter()const{return _center;}
    inline const QList<QString> &getSfacArray()const{return sfacarray;}
    inline const QList<double> &getUnitArray()const{return unitarray;}
    inline const CellType &getBrave()const{return _ctype;}
    inline bool isBad()const{
        if (_a == 1 || _b == 1 || _c == 1)
            return true;
        else
            return false;
    }

    inline void setPath(const QString &path){_path=path;}
    inline void setFileType(const FileType &a){_type = a;}
    inline void setCellType(const CellType &a){_ctype = a;}
    inline void setWavelength(const double &a){_wavelength = a;}
    inline void setCenter(const bool &a){_center = a;}
    inline void setSfacArray(const QList<QString> &a){sfacarray = a;}
    inline void setUnitArray(const QList<double> &a){unitarray = a;}

    friend QDataStream& operator<<(QDataStream& out, const Crystfile& crfile);
    friend QDataStream& operator>>(QDataStream& in, Crystfile& crfile);

private:
    QString _path;
    FileType _type;
    CellType _ctype;

    double _wavelength;
    bool _center;
    QList<QString> sfacarray;
    QList<double> unitarray;

    void parseINS();
    void parseCIF();
};

Q_DECLARE_METATYPE(Crystfile)

#endif // CRYSTFILE_H

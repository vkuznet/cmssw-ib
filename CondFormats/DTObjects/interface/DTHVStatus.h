#ifndef DTHVStatus_H
#define DTHVStatus_H
/** \class DTHVStatus
 *
 *  Description:
 *       Class to hold high voltage status
 *             ( half layer by half layer )
 *
 *  $Date: 2010/01/20 18:20:08 $
 *  $Revision: 1.3 $
 *  \author Paolo Ronchese INFN Padova
 *
 */

//----------------------
// Base Class Headers --
//----------------------


//------------------------------------
// Collaborating Class Declarations --
//------------------------------------
#include "CondFormats/DTObjects/interface/DTBufferTree.h"
class DTWireId;
class DTLayerId;
class DTChamberId;

//---------------
// C++ Headers --
//---------------
#include <string>
#include <vector>
#if !defined(__CINT__) && !defined(__MAKECINT__) && !defined(__REFLEX__)
#include <atomic>
#endif

//              ---------------------
//              -- Class Interface --
//              ---------------------

class DTHVStatusId {

 public:

  DTHVStatusId();
  ~DTHVStatusId();

  int   wheelId;
  int stationId;
  int  sectorId;
  int      slId;
  int   layerId;
  int    partId;

};


class DTHVStatusData {

 public:

  DTHVStatusData();
  ~DTHVStatusData();

  int fCell;
  int lCell;
  int flagA;
  int flagC;
  int flagS;

};


class DTHVStatus {

 public:

  /** Constructor
   */
  DTHVStatus();
  DTHVStatus( const std::string& version );

  /** Destructor
   */
  ~DTHVStatus();

  /** Operations
   */
  /// get content
  int get( int   wheelId,
           int stationId,
           int  sectorId,
           int      slId,
           int   layerId,
           int    partId,
           int&    fCell,
           int&    lCell,
           int&    flagA,
           int&    flagC,
           int&    flagS ) const;
  int get( const DTLayerId& id,
           int    partId,
           int&    fCell,
           int&    lCell,
           int&    flagA,
           int&    flagC,
           int&    flagS ) const;
  int get( const DTWireId& id,
           int&         flagA,
           int&         flagC,
           int&         flagS ) const;
  int offChannelsNumber() const; 
  int offChannelsNumber( const DTChamberId& id ) const; 
  int badChannelsNumber() const; 
  int badChannelsNumber( const DTChamberId& id ) const; 
  /// access version
  const
  std::string& version() const;
  std::string& version();

  /// reset content
  void clear();

  int set( int   wheelId,
           int stationId,
           int  sectorId,
           int      slId,
           int   layerId,
           int    partId,
           int     fCell,
           int     lCell,
           int     flagA,
           int     flagC,
           int     flagS );
  int set( const DTLayerId& id,
           int    partId,
           int     fCell,
           int     lCell,
           int     flagA,
           int     flagC,
           int     flagS );
  int setFlagA( int   wheelId,
                int stationId,
                int  sectorId,
                int      slId,
                int   layerId,
                int    partId,
                int      flag );
  int setFlagA( const DTLayerId& id,
                int    partId,
                int      flag );
  int setFlagC( int   wheelId,
                int stationId,
                int  sectorId,
                int      slId,
                int   layerId,
                int    partId,
                int      flag );
  int setFlagC( const DTLayerId& id,
                int    partId,
                int      flag );
  int setFlagS( int   wheelId,
                int stationId,
                int  sectorId,
                int      slId,
                int   layerId,
                int    partId,
                int      flag );
  int setFlagS( const DTLayerId& id,
                int    partId,
                int      flag );

  /// Access methods to data
  typedef std::vector< std::pair<DTHVStatusId,
                                 DTHVStatusData> >::const_iterator
                                                    const_iterator;
  const_iterator begin() const;
  const_iterator end() const;

 private:
#if !defined(__CINT__) && !defined(__MAKECINT__) && !defined(__REFLEX__)
  // copy-ctor
  DTHVStatus(const DTHVStatus& src) = delete;
  // copy assignment operator
  DTHVStatus& operator=(const DTHVStatus& rhs) = delete;
#else
  // copy-ctor
  DTHVStatus(const DTHVStatus& src);
  // copy assignment operator
  DTHVStatus& operator=(const DTHVStatus& rhs);
#endif

  std::string dataVersion;

  std::vector< std::pair<DTHVStatusId,DTHVStatusData> > dataList;

#if !defined(__CINT__) && !defined(__MAKECINT__) && !defined(__REFLEX__)
  mutable std::atomic<DTBufferTree<int,int>*> dBuf;
#else
  mutable DTBufferTree<int,int>* dBuf;
#endif

  /// read and store full content
  void cacheMap() const;
  std::string mapName() const;

};

#endif // DTHVStatus_H


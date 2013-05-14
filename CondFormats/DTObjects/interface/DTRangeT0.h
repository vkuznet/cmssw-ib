#ifndef DTRangeT0_H
#define DTRangeT0_H
/** \class DTRangeT0
 *
 *  Description:
 *       Class to hold drift tubes T0 range
 *             ( SL by SL min - max T0 )
 *
 *  $Date: 2010/01/20 18:20:08 $
 *  $Revision: 1.4 $
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
#include "DataFormats/MuonDetId/interface/DTSuperLayerId.h"

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

class DTRangeT0Id {

 public:

  DTRangeT0Id();
  ~DTRangeT0Id();

  int   wheelId;
  int stationId;
  int  sectorId;
  int      slId;

};


class DTRangeT0Data {

 public:

  DTRangeT0Data();
  ~DTRangeT0Data();

  int t0min;
  int t0max;

};


class DTRangeT0 {

 public:

  /** Constructor
   */
  DTRangeT0();
  DTRangeT0( const std::string& version );

  /** Destructor
   */
  ~DTRangeT0();

  /** Operations
   */
  /// get content
  int slRangeT0( int   wheelId,
                 int stationId,
                 int  sectorId,
                 int      slId,
                 int&    t0min,
                 int&    t0max ) const
      { return get( wheelId, stationId, sectorId, slId,
                    t0min, t0max ); };
  int slRangeT0( const DTSuperLayerId& id,
                 int&    t0min,
                 int&    t0max ) const
      { return get( id, t0min, t0max ); };
  int get( int   wheelId,
           int stationId,
           int  sectorId,
           int      slId,
           int&    t0min,
           int&    t0max ) const;
  int get( const DTSuperLayerId& id,
           int&    t0min,
           int&    t0max ) const;

  /// access version
  const
  std::string& version() const;
  std::string& version();

  /// reset content
  void clear();

  int setSLRangeT0( int   wheelId,
                    int stationId,
                    int  sectorId,
                    int      slId,
                    int     t0min,
                    int     t0max )
      { return set( wheelId, stationId, sectorId, slId, t0min, t0max ); };
  int setSLRangeT0( const DTSuperLayerId& id,
                    int     t0min,
                    int     t0max )
      { return set( id, t0min, t0max ); };
  int set( int   wheelId,
           int stationId,
           int  sectorId,
           int      slId,
           int     t0min,
           int     t0max );
  int set( const DTSuperLayerId& id,
           int     t0min,
           int     t0max );

  /// Access methods to data
  typedef std::vector< std::pair<DTRangeT0Id,
                                 DTRangeT0Data> >::const_iterator
                                                   const_iterator;
  const_iterator begin() const;
  const_iterator end() const;

 private:
#if !defined(__CINT__) && !defined(__MAKECINT__) && !defined(__REFLEX__)
  // copy-ctor
  DTRangeT0(const DTRangeT0& src) = delete;
  // copy assignment operator
  DTRangeT0& operator=(const DTRangeT0& rhs) = delete;
#else
  // copy-ctor
  DTRangeT0(const DTRangeT0& src);
  // copy assignment operator
  DTRangeT0& operator=(const DTRangeT0& rhs);
#endif

  std::string dataVersion;

  std::vector< std::pair<DTRangeT0Id,DTRangeT0Data> > dataList;

#if !defined(__CINT__) && !defined(__MAKECINT__) && !defined(__REFLEX__)
  mutable std::atomic<DTBufferTree<int,int>*> dBuf;
#else
  mutable DTBufferTree<int,int>* dBuf;
#endif

  /// read and store full content
  void cacheMap() const;
  std::string mapName() const;

};


#endif // DTRangeT0_H


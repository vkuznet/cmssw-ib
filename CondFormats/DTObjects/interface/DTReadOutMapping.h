#ifndef DTReadOutMapping_H
#define DTReadOutMapping_H
/** \class DTReadOutMapping
 *
 *  Description:
 *       Class to map read-out channels to physical drift tubes
 *
 *  $Date: 2011/02/08 15:48:27 $
 *  $Revision: 1.8 $
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
#include "DataFormats/MuonDetId/interface/DTWireId.h"

//---------------
// C++ Headers --
//---------------
#include <vector>
#include <string>
#if !defined(__CINT__) && !defined(__MAKECINT__) && !defined(__REFLEX__)
#include <atomic>
#endif

//              ---------------------
//              -- Class Interface --
//              ---------------------

class DTReadOutGeometryLink {

 public:

  DTReadOutGeometryLink();
  ~DTReadOutGeometryLink();

  int     dduId;
  int     rosId;
  int     robId;
  int     tdcId;
  int channelId;
  int   wheelId;
  int stationId;
  int  sectorId;
  int      slId;
  int   layerId;
  int    cellId;

};


class DTReadOutMapping {

 public:

  /** Constructor
   */
  DTReadOutMapping();
  DTReadOutMapping( const std::string& cell_map_version,
                    const std::string&  rob_map_version );

  /** Destructor
   */
  ~DTReadOutMapping();

  enum type { plain, compact };

  /** Operations
   */
  /// transform identifiers
  int readOutToGeometry( int      dduId,
                         int      rosId,
                         int      robId,
                         int      tdcId,
                         int  channelId,
                         DTWireId& wireId ) const;

  int readOutToGeometry( int      dduId,
                         int      rosId,
                         int      robId,
                         int      tdcId,
                         int  channelId,
                         int&   wheelId,
                         int& stationId,
                         int&  sectorId,
                         int&      slId,
                         int&   layerId,
                         int&    cellId ) const;

  int geometryToReadOut( int    wheelId,
                         int  stationId,
                         int   sectorId,
                         int       slId,
                         int    layerId,
                         int     cellId,
                         int&     dduId,
                         int&     rosId,
                         int&     robId,
                         int&     tdcId,
                         int& channelId ) const;
  int geometryToReadOut( const DTWireId& wireId,
                         int&     dduId,
                         int&     rosId,
                         int&     robId,
                         int&     tdcId,
                         int& channelId ) const;

  type mapType() const;

  /// access parent maps identifiers
  const
  std::string& mapCellTdc() const;
  std::string& mapCellTdc();
  const
  std::string& mapRobRos() const;
  std::string& mapRobRos();

  /// clear map
  void clear();

  /// insert connection
  int insertReadOutGeometryLink( int     dduId,
                                 int     rosId,
                                 int     robId,
                                 int     tdcId,
                                 int channelId,
                                 int   wheelId,
                                 int stationId,
                                 int  sectorId,
                                 int      slId,
                                 int   layerId,
                                 int    cellId );

  /// Access methods to the connections
  typedef std::vector<DTReadOutGeometryLink>::const_iterator const_iterator;
  const_iterator begin() const;
  const_iterator end() const;

  /// Expand to full map
  const DTReadOutMapping* fullMap() const;

 private:
#if !defined(__CINT__) && !defined(__MAKECINT__) && !defined(__REFLEX__)
  // copy-ctor
  DTReadOutMapping(const DTReadOutMapping& src) = delete;
  // copy assignment operator
  DTReadOutMapping& operator=(const DTReadOutMapping& rhs) = delete;
#else
  // copy-ctor
  DTReadOutMapping(const DTReadOutMapping& src);
  // copy assignment operator
  DTReadOutMapping& operator=(const DTReadOutMapping& rhs);
#endif

  std::string cellMapVersion;
  std::string  robMapVersion;

  std::vector<DTReadOutGeometryLink> readOutChannelDriftTubeMap;

#if !defined(__CINT__) && !defined(__MAKECINT__) && !defined(__REFLEX__)
  mutable std::atomic<DTBufferTree<int,int>*> mType;
  mutable std::atomic<DTBufferTree<int,int>*> rgBuf;
  mutable std::atomic<DTBufferTree<int,int>*> rgROB;
  mutable std::atomic<DTBufferTree<int,int>*> rgROS;
  mutable std::atomic<DTBufferTree<int,int>*> rgDDU;
  mutable std::atomic<DTBufferTree<int,int>*> grBuf;
  mutable std::atomic<DTBufferTree<int,std::vector<int>*>*> grROB;
  mutable std::atomic<DTBufferTree<int,std::vector<int>*>*> grROS;
  mutable std::atomic<DTBufferTree<int,std::vector<int>*>*> grDDU;
#else
  mutable DTBufferTree<int,int>* mType;
  mutable DTBufferTree<int,int>* rgBuf;
  mutable DTBufferTree<int,int>* rgROB;
  mutable DTBufferTree<int,int>* rgROS;
  mutable DTBufferTree<int,int>* rgDDU;
  mutable DTBufferTree<int,int>* grBuf;
  mutable DTBufferTree<int,std::vector<int>*>* grROB;
  mutable DTBufferTree<int,std::vector<int>*>* grROS;
  mutable DTBufferTree<int,std::vector<int>*>* grDDU;
#endif

  /// read and store full content
  void cacheMap() const;
  std::string mapNameRG() const;
  std::string mapNameGR() const;

};


#endif // DTReadOutMapping_H


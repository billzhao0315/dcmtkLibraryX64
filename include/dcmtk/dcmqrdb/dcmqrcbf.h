/*
 *
 *  Copyright (C) 1993-2010, OFFIS e.V.
 *  All rights reserved.  See COPYRIGHT file for details.
 *
 *  This software and supporting documentation were developed by
 *
 *    OFFIS e.V.
 *    R&D Division Health
 *    Escherweg 2
 *    D-26121 Oldenburg, Germany
 *
 *
 *  Module:  dcmqrdb
 *
 *  Author:  Marco Eichelberg
 *
 *  Purpose: class DcmQueryRetrieveFindContext
 *
 *  Last Update:      $Author: joergr $
 *  Update Date:      $Date: 2010-10-14 13:16:41 $
 *  CVS/RCS Revision: $Revision: 1.4 $
 *  Status:           $State: Exp $
 *
 *  CVS/RCS Log at end of file
 *
 */

#ifndef DCMQRCBF_H
#define DCMQRCBF_H

#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */
#include "dcmtk/dcmnet/dimse.h"

class DcmQueryRetrieveDatabaseHandle;
class DcmQueryRetrieveOptions;

/** this class maintains the context information that is passed to the
 *  callback function called by DIMSE_findProvider.
 */
class DcmQueryRetrieveFindContext
{
public:
    /** constructor
     *  @param handle reference to database handle
     *  @param options options for the Q/R service
     *  @param priorStat prior DIMSE status
     */
    DcmQueryRetrieveFindContext(
      DcmQueryRetrieveDatabaseHandle& handle,
      const DcmQueryRetrieveOptions& options,
      DIC_US priorStat)
    : dbHandle(handle)
    , options_(options)
    , priorStatus(priorStat)
    , ourAETitle()
    {
    }

    /** set the AEtitle under which this application operates
     *  @param ae AEtitle, is copied into this object.
     */
    void setOurAETitle(const char *ae)
    {
      if (ae) ourAETitle = ae; else ourAETitle.clear();
    }

    /** callback handler called by the DIMSE_storeProvider callback function.
     *  @param cancelled (in) flag indicating whether a C-CANCEL was received
     *  @param request original find request (in)
     *  @param requestIdentifiers original find request identifiers (in)
     *  @param responseCount find response count (in)
     *  @param response find response (out)
     *  @param responseIdentifiers find response identifiers (out)
     *  @param stDetail status detail for find response (out)
     */
    void callbackHandler(
        OFBool cancelled, T_DIMSE_C_FindRQ *request,
        DcmDataset *requestIdentifiers, int responseCount,
        T_DIMSE_C_FindRSP *response,
        DcmDataset **responseIdentifiers,
        DcmDataset **stDetail);

private:

    /// reference to database handle
    DcmQueryRetrieveDatabaseHandle& dbHandle;

    /// reference to Q/R service options
    const DcmQueryRetrieveOptions& options_;

    /// prior DIMSE status
    DIC_US priorStatus;

    /// our current title
    OFString ourAETitle;

};

#endif

/*
 * CVS Log
 * $Log: dcmqrcbf.h,v $
 * Revision 1.4  2010-10-14 13:16:41  joergr
 * Updated copyright header. Added reference to COPYRIGHT file.
 *
 * Revision 1.3  2009-08-21 09:50:07  joergr
 * Replaced tabs by spaces and updated copyright date.
 *
 * Revision 1.2  2005/12/08 16:04:16  meichel
 * Changed include path schema for all DCMTK header files
 *
 * Revision 1.1  2005/03/30 13:34:50  meichel
 * Initial release of module dcmqrdb that will replace module imagectn.
 *   It provides a clear interface between the Q/R DICOM front-end and the
 *   database back-end. The imagectn code has been re-factored into a minimal
 *   class structure.
 *
 *
 */

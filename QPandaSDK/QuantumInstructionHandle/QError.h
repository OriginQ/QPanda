#ifndef _QERROR_H
#define _QERROR_H
enum QError
{
    qErrorNone = 2,
    undefineError,
    qParameterError,
    qbitError,
    loadFileError,
    initStateError,
    destroyStateError,
    setComputeUnitError,
    runProgramError,
    getResultError,
    getQStateError,
    notReadFileError
};

#endif

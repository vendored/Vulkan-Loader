//
// File: vk_dbg.h
//
/*
** Copyright (c) 2015 The Khronos Group Inc.
**
** Permission is hereby granted, free of charge, to any person obtaining a
** copy of this software and/or associated documentation files (the
** "Materials"), to deal in the Materials without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Materials, and to
** permit persons to whom the Materials are furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be included
** in all copies or substantial portions of the Materials.
**
** THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
** CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
** TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
** MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
*/

#ifndef __VK_DBG_H__
#define __VK_DBG_H__

#include "vulkan.h"

#define VK_DEBUG_REPORT_EXTENSION_NUMBER 2
#define VK_DEBUG_REPORT_EXTENSION_VERSION 1
#define VK_DEBUG_MARKER_EXTENSION_NUMBER 3
#define VK_DEBUG_MARKER_EXTENSION_VERSION 1
#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*
***************************************************************************************************
*   DebugReport and DebugMarker Vulkan Extension API
***************************************************************************************************
*/

#define DEBUG_REPORT_EXTENSION_NAME "DEBUG_REPORT"
#define DEBUG_MARKER_EXTENSION_NAME "DEBUG_MARKER"

VK_DEFINE_NONDISP_SUBCLASS_HANDLE(VkDbgMsgCallback, VkObject)

// ------------------------------------------------------------------------------------------------
// Enumerations

typedef enum VkDbgReportFlags_
{
    VK_DBG_REPORT_INFO_BIT       = VK_BIT(0),
    VK_DBG_REPORT_WARN_BIT       = VK_BIT(1),
    VK_DBG_REPORT_PERF_WARN_BIT  = VK_BIT(2),
    VK_DBG_REPORT_ERROR_BIT      = VK_BIT(3),
} VkDbgReportFlags;

#define VK_DBG_ENUM_EXTEND(type, id)    ((type)(VK_DEBUG_MARKER_EXTENSION_NUMBER * -1000 + (id)))

#define VK_OBJECT_INFO_TYPE_DBG_OBJECT_TAG VK_DBG_ENUM_EXTEND(VkObjectInfoType, 0)
#define VK_OBJECT_INFO_TYPE_DBG_OBJECT_NAME VK_DBG_ENUM_EXTEND(VkObjectInfoType, 1)

#define VK_OBJECT_TYPE_MSG_CALLBACK VK_DBG_ENUM_EXTEND(VkObjectType, 0)
// ------------------------------------------------------------------------------------------------
// Vulkan function pointers

typedef void (*PFN_vkDbgMsgCallback)(
    VkFlags                             msgFlags,
    VkObjectType                        objType,
    VkObject                            srcObject,
    size_t                              location,
    int32_t                             msgCode,
    const char*                         pLayerPrefix,
    const char*                         pMsg,
    void*                               pUserData);

// ------------------------------------------------------------------------------------------------
// API functions

typedef VkResult (VKAPI *PFN_vkDbgCreateMsgCallback)(VkInstance instance, VkFlags msgFlags, const PFN_vkDbgMsgCallback pfnMsgCallback, void* pUserData, VkDbgMsgCallback* pMsgCallback);
typedef VkResult (VKAPI *PFN_vkDbgDestroyMsgCallback)(VkInstance instance, VkDbgMsgCallback pMsgCallback);
typedef void (VKAPI *PFN_vkDbgStringCallback)(VkFlags msgFlags, VkObjectType objType, VkObject srcObject, size_t location, int32_t msgCode, const char* pLayerPrefix, const char* pMsg, void* pUserData);
typedef void (VKAPI *PFN_vkDbgStdioCallback)(VkFlags msgFlags, VkObjectType objType, VkObject srcObject, size_t location, int32_t msgCode, const char* pLayerPrefix, const char* pMsg, void* pUserData);
typedef void (VKAPI *PFN_vkDbgBreakCallback)(VkFlags msgFlags, VkObjectType objType, VkObject srcObject, size_t location, int32_t msgCode, const char* pLayerPrefix, const char* pMsg, void* pUserData);
typedef void (VKAPI *PFN_vkCmdDbgMarkerBegin)(VkCmdBuffer cmdBuffer, const char* pMarker);
typedef void (VKAPI *PFN_vkCmdDbgMarkerEnd)(VkCmdBuffer cmdBuffer);
typedef VkResult (VKAPI *PFN_vkDbgSetObjectTag)(VkDevice device, VkObjectType objType, VkObject object, size_t tagSize, const void* pTag);
typedef VkResult (VKAPI *PFN_vkDbgSetObjectName)(VkDevice device, VkObjectType objType, VkObject object, size_t nameSize, const char* pName);

#ifdef VK_PROTOTYPES

// DebugReport extension entrypoints
VkResult VKAPI vkDbgCreateMsgCallback(
    VkInstance                          instance,
    VkFlags                             msgFlags,
    const PFN_vkDbgMsgCallback          pfnMsgCallback,
    void*                               pUserData,
    VkDbgMsgCallback*                   pMsgCallback);

VkResult VKAPI vkDbgDestroyMsgCallback(
    VkInstance                          instance,
    VkDbgMsgCallback                    pMsgCallback);

// DebugReport utility callback functions
void VKAPI vkDbgStringCallback(
    VkFlags                             msgFlags,
    VkObjectType                        objType,
    VkObject                            srcObject,
    size_t                              location,
    int32_t                             msgCode,
    const char*                         pLayerPrefix,
    const char*                         pMsg,
    void*                               pUserData);

void VKAPI vkDbgStdioCallback(
    VkFlags                             msgFlags,
    VkObjectType                        objType,
    VkObject                            srcObject,
    size_t                              location,
    int32_t                             msgCode,
    const char*                         pLayerPrefix,
    const char*                         pMsg,
    void*                               pUserData);

void VKAPI vkDbgBreakCallback(
    VkFlags                             msgFlags,
    VkObjectType                        objType,
    VkObject                            srcObject,
    size_t                              location,
    int32_t                             msgCode,
    const char*                         pLayerPrefix,
    const char*                         pMsg,
    void*                               pUserData);

// DebugMarker extension entrypoints
void VKAPI vkCmdDbgMarkerBegin(
    VkCmdBuffer                         cmdBuffer,
    const char*                         pMarker);

void VKAPI vkCmdDbgMarkerEnd(
    VkCmdBuffer                         cmdBuffer);

VkResult VKAPI vkDbgSetObjectTag(
    VkDevice                            device,
    VkObjectType                        objType,
    VkObject                            object,
    size_t                              tagSize,
    const void*                         pTag);

VkResult VKAPI vkDbgSetObjectName(
    VkDevice                            device,
    VkObjectType                        objType,
    VkObject                            object,
    size_t                              nameSize,
    const char*                         pName);

#endif // VK_PROTOTYPES

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // __VK_DBG_H__

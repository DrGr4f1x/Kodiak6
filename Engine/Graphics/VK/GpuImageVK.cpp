//
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
// Author:  David Elder
//

#include "Stdafx.h"

#include "GpuImageVK.h"


namespace Kodiak::VK
{

GpuImage::GpuImage(ResourceType resourceType, CVkImage* image, ResourceState usageState) noexcept
	: m_resourceType{ resourceType }
	, m_image{ image }
	, m_usageState{ usageState }
{}

} // namespace Kodiak::VK
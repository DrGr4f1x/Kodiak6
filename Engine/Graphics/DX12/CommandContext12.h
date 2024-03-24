//
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
// Author:  David Elder
//

#pragma once

#include "Graphics\Interfaces.h"

namespace Kodiak::DX12
{

struct CommandContextState
{

};


class CommandContext : public IntrusiveCounter<ICommandContext>, public NonCopyable, private CommandContextState
{
public:
	~CommandContext() override;

	void Finish(bool bWaitForCompletion = false) final;

	void BeginEvent(const std::string& label);
	void EndEvent();
	void SetMarker(const std::string& label);
};


class GraphicsContext : public IntrusiveCounter<IGraphicsContext>, public NonCopyable, private CommandContextState
{
public:
	~GraphicsContext() override;
};


class ComputeContext : public IntrusiveCounter<IComputeContext>, public NonCopyable, private CommandContextState
{
public:
	~ComputeContext() override;
};

} // namespace Kodiak::DX12
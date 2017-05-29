#include <IModuleImpl.h>

namespace Modules
{
namespace Impl
{
namespace Null
{
class CModuleImpl final : public IModuleImpl
{
public:

	CModuleImpl() = default;
	virtual ~CModuleImpl() override = default;
	CModuleImpl(CModuleImpl const&) = delete;
	CModuleImpl(CModuleImpl&&) = delete;
	CModuleImpl& operator=(CModuleImpl const&) = delete;
	CModuleImpl& operator=(CModuleImpl&&) = delete;

	// IModuleImpl
	virtual string GetString() override;
	// ~IModuleImpl
};
}
}
}
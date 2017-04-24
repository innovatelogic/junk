#pragma once

namespace junk
{
    namespace is_derived_probe_a
    {
        template<typename D, typename B>
        class IsDerivedClassHelper
        {
            class No{};
            class Yes { No no[3]; };

            static Yes test(B*);
            static No test(...);
        public:
            enum { Is = sizeof(test(static_cast<D*>(nullptr))) == sizeof(Yes) };
        };

        template<class C, class P>
        bool IsDerivedClass(){
            return IsDerivedClassHelper<C, P>::Is;
        };
    }
}
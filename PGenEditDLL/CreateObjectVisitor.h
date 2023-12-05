#pragma once
#include <rttr/visitor.h>

class CreateObjectVisitor : public rttr::visitor
{
public:
    template<typename T>
    void visit_type_begin(const type_info<T>& info) {}

    template<typename T>
    void visit_type_end(const type_info<T>& info) {}

    template<typename T>
    void visit_constructor(const constructor_info<T>& info)
    {
        auto params = info.ctor_item.get_parameter_infos();
        // get number of default parameters
        size_t defaultParams = 0;
        for (auto& param : params)
        {
            if (param.has_default_value())
            {
                ++defaultParams;
            }
        }
        if (params.size() == 0 || params.size() == defaultParams) // default constructor or all parameters have default values
        {
            result = info.ctor_item.invoke();
        }
        else
        {

        }
    }

    template<typename T>
    void visit_constructor_function(const constructor_function_info<T>& info) {}

    template<typename T>
    void visit_method(const method_info<T>& info) {}

    template<typename T>
    void visit_global_method(const method_info<T>& info) {}

    RTTR_ENABLE(rttr::visitor);

public:
    rttr::variant& result;
    CreateObjectVisitor(rttr::variant& result) : result(result) {}
};

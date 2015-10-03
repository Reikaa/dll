//=======================================================================
// Copyright (c) 2014-2015 Baptiste Wicht
// Distributed under the terms of the MIT License.
// (See accompanying file LICENSE or copy at
//  http://opensource.org/licenses/MIT)
//=======================================================================

#include "dll/dyn_rbm.hpp"
#include "dll/dbn.hpp"
#include "dll/ocv_visualizer.hpp"

template<typename DBN>
void test_dbn(DBN& dbn){
    dbn->display();

    std::vector<etl::dyn_vector<float>> images;

    dbn->pretrain(images, 10);
}

int main(){
    using dbn_t =
        dll::dbn_desc<
            dll::dbn_layers<
                dll::dyn_rbm_desc<dll::momentum, dll::init_weights>::rbm_t,
                dll::dyn_rbm_desc<dll::momentum>::rbm_t,
                dll::dyn_rbm_desc<dll::momentum, dll::hidden<dll::unit_type::SOFTMAX>>::rbm_t
        >, dll::watcher<dll::opencv_dbn_visualizer>
        >::dbn_t;

    auto dbn = std::make_unique<dbn_t>();

    dbn->template layer_get<0>().init_rbm(28 * 28, 100);
    dbn->template layer_get<1>().init_rbm(100, 200);
    dbn->template layer_get<2>().init_rbm(200, 10);

    test_dbn(dbn);

    return 0;
}


dnn_fallback_kernel={


convolution_2d: function(input_arrays, output_arrays, option) {
var x = input_arrays[0];
var w = input_arrays[1];
var y = output_arrays[0];
var n = option.n | 0;
var in_spatial = option.in_spatial;
var out_spatial = option.out_spatial;
var out_size = option.out_size | 0;
var in_size = option.in_size | 0;
var padding = option.padding;
var stride = option.stride;
var ksize = option.ksize;
var dilation_rate = option.dilation_rate;
var strides_x = option.strides_x;
var strides_w = option.strides_w;
var strides_y = option.strides_y;

var get_x = function(n_, y_, x_, c_) {
  y_ -= padding[0];
  x_ -= padding[1];
  if (y_ < 0 || y_ >= in_spatial[0] || x_ < 0 || x_ >= in_spatial[1]) {
    return 0.0;
  }
  var idx = n_ * strides_x[0] + y_ * strides_x[1] + x_ * strides_x[2] + c_ * strides_x[3];
  return x[idx];
};

var get_w = function(ky_, kx_, in_c, out_c) {
  var idx = out_c * strides_w[0] + ky_ * strides_w[1] + kx_ * strides_w[2] + in_c * strides_w[3];
  return w[idx];
};

var set_y = function(n_, y_, x_, c_, val) {
  var idx = n_ * strides_y[0] + y_ * strides_y[1] + x_ * strides_y[2] + c_ * strides_y[3];
  y[idx] = val;
};

for (var batch = 0; batch < n; batch++) {
  for (var oy = 0; oy < out_spatial[0]; oy++) {
    for (var ox = 0; ox < out_spatial[1]; ox++) {
      for (var oc = 0; oc < out_size; oc++) {
        var sum = 0.0;
        for (var ky = 0; ky < ksize[0]; ky++) {
          for (var kx = 0; kx < ksize[1]; kx++) {
            for (var ic = 0; ic < in_size; ic++) {
              sum += get_x(batch, oy * stride[0] + ky * dilation_rate[0],
                           ox * stride[1] + kx * dilation_rate[1],
                           ic) *
                     get_w(ky, kx, ic, oc);
            }
          }
        }
        set_y(batch, oy, ox, oc, sum);
      }
    }
  }
}

},



elementwiseadd_653f37079602765521bb5cca1b07d2b80af153b45cd96b6cf18bb657: function(input_arrays, output_arrays, option) {
    var v1 = input_arrays[0];
    var v2 = input_arrays[1];
    var v3 = input_arrays[2];
    var v4 = option['7'];
    var v5 = option['9'];
    var D0 = option['11'];
    var D1 = option['13'];
    var d0;
    for (d0 = ((1 > 8) ? (0 % (1 / 8)) : 0); d0 < D0; d0 += ((1 > 8) ? (1 / 8) : 1)) {
        var v6 = v1[d0];
        var d1;
        for (d1 = ((1 > 8) ? (0 / (1 / 8)) : 0); d1 < D1; d1 += ((1 > 8) ? 8 : 1)) {
            var v7 = v2[d0 + d1*v4];
            var v8;
            (function(){
                v8 = v7 + v6;
            })();
            v3[d0 + d1*v5] = v8;
        }
    }
},

relu_3693ec08de79c27ab35127ab0a10897afa2249f09efd879f2a8158d1: function(input_arrays, output_arrays, option) {
    var v1 = input_arrays[0];
    var v2 = input_arrays[1];
    var D0 = option['5'];
    var d0;
    for (d0 = 0; d0 < D0; d0 += 1) {
        var v3 = v1[d0];
        var v4;
        (function(){
            v4 = v3 > 0 ? v3 : 0;
        })();
        v2[d0] = v4;
    }
},

max_pooling_2d: function(input_arrays, output_arrays, option) {
var x = input_arrays[0];
var y = output_arrays[0];
var n = option.n | 0;
var in_spatial = option.in_spatial;
var out_spatial = option.out_spatial;
var out_size = option.out_size | 0;
var in_size = option.in_size | 0;
var padding = option.padding;
var stride = option.stride;
var ksize = option.ksize;
var strides_x = option.strides_x;
var strides_y = option.strides_y;

var get_x = function(n_, y_, x_, c_) {
  y_ -= padding[0];
  x_ -= padding[1];
  if (y_ < 0 || y_ >= in_spatial[0] || x_ < 0 || x_ >= in_spatial[1]) {
    return -Infinity;
  }
  var idx = n_ * strides_x[0] + y_ * strides_x[1] + x_ * strides_x[2] + c_ * strides_x[3];
  return x[idx];
};

var set_y = function(n_, y_, x_, c_, val) {
  var idx = n_ * strides_y[0] + y_ * strides_y[1] + x_ * strides_y[2] + c_ * strides_y[3];
  y[idx] = val;
};

for (var batch = 0; batch < n; batch++) {
  for (var oy = 0; oy < out_spatial[0]; oy++) {
    for (var ox = 0; ox < out_spatial[1]; ox++) {
      for (var oc = 0; oc < out_size; oc++) {
        var window_max = -Infinity;
        for (var ky = 0; ky < ksize[0]; ky++) {
          for (var kx = 0; kx < ksize[1]; kx++) {
            var val = get_x(batch, oy * stride[0] + ky, ox * stride[1] + kx, oc);
            if (val > window_max) {
              window_max = val;
            }
          }
        }
        set_y(batch, oy, ox, oc, window_max);
      }
    }
  }
}

},



concat: function(input_arrays, output_arrays, option) {
var xs = input_arrays;
var y = output_arrays[0];
var shapes = option.x_shapes;
var strides = option.x_strides;
var offsets = option.x_offsets;
var x;
var offset;
var stride;
var shape;
var position;

for (var i = 0; i < xs.length; i++) {
    x = xs[i];
    offset = offsets[i];
    stride = strides[i];
    shape = shapes[i];
    position = [];
    
    for (var j = 0; j < shape.length; j++) {
        position[j] = 0;
    }
    
    do {
        y[offset + dot(stride, position)] = get(x, shape, position);
    } while (increment(shape, position))
}

function dot(a, b) {
    var sum = 0;
    for (var i = 0; i < a.length; i++) {
        sum += a[i] * b[i];
    }
    return sum;
}

function get(x, shape, position) {
    var i = 0;
    for (var j = 0; j < shape.length; j++) {
        i = (i * shape[j]) + position[j];
    }
    return x[i];
}

function increment(shape, position) {
    var d = shape.length - 1;
    position[d]++;
    
    while (position[d] === shape[d]) {
        if (d == 0) return false;

        position[d] -= shape[d];
        d--;
        position[d]++;
    }
    
    return true;
}

},


average_pooling_2d: function(input_arrays, output_arrays, option) {
var x = input_arrays[0];
var y = output_arrays[0];
var n = option.n | 0;
var in_spatial = option.in_spatial;
var out_spatial = option.out_spatial;
var out_size = option.out_size | 0;
var padding = option.padding;
var stride = option.stride;
var ksize = option.ksize;
var strides_x = option.strides_x;
var strides_y = option.strides_y;
var window_area_inv = 1.0 / (ksize[0] * ksize[1]);

var get_x = function(n_, y_, x_, c_) {
  y_ -= padding[0];
  x_ -= padding[1];
  if (y_ < 0 || y_ >= in_spatial[0] || x_ < 0 || x_ >= in_spatial[1]) {
    return 0.0;
  }
  var idx = n_ * strides_x[0] + y_ * strides_x[1] + x_ * strides_x[2] + c_ * strides_x[3];
  return x[idx];
};

var set_y = function(n_, y_, x_, c_, val) {
  var idx = n_ * strides_y[0] + y_ * strides_y[1] + x_ * strides_y[2] + c_ * strides_y[3];
  y[idx] = val;
};

for (var batch = 0; batch < n; batch++) {
  for (var oy = 0; oy < out_spatial[0]; oy++) {
    for (var ox = 0; ox < out_spatial[1]; ox++) {
      for (var oc = 0; oc < out_size; oc++) {
        var sum = 0.0;
        for (var ky = 0; ky < ksize[0]; ky++) {
          for (var kx = 0; kx < ksize[1]; kx++) {
            sum += get_x(batch, oy * stride[0] + ky, ox * stride[1] + kx, oc);
          }
        }
        set_y(batch, oy, ox, oc, sum * window_area_inv);
      }
    }
  }
}

},



reshape: function(input_arrays, output_arrays, option) {
var x = input_arrays[0];
var y = output_arrays[0];
var length = option.length | 0;

for (var i = 0; i < length; i++) {
  y[i] = x[i];
}

},



softmax: function(input_arrays, output_arrays, option) {
var x = input_arrays[0];
var y = output_arrays[0];
var N = option.N | 0;
var C = option.C | 0;

for (var n = 0; n < N; n++) {
    var set_max = x[n * C];
    for (var c = 0; c < C; c++) {
        var val = x[n * C + c];
        if (val > set_max) {
            set_max = val;
        }
    }

    var sum_exp = 0.0;
    for (var c = 0; c < C; c++) {
        var val = x[n * C + c];
        var exp_x = Math.exp(val - set_max);
        sum_exp += exp_x;
        y[n * C + c] = exp_x;
    }

    for (var c = 0; c < C; c++) {
        y[n * C + c] /= sum_exp;
    }
}
},



};

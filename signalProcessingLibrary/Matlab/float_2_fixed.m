% converting a floating point to Q32 fixed representation

init = 0.78539816339744830961566084581988;
for i = 0:19
    val = init / (2^i);

    dec_val_fixed = floor((val * (2^32)));

    dec2hex(dec_val_fixed)
end
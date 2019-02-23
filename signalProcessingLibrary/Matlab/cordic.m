% CORDIC algorithm

x = 1;
y = 0;

phi = 30;

z = phi;
k = 1;  
for n = 0:10
    if z > 0
        d = +1;
    else
        d = -1;
    end
    x1 = x - (y * d * (1/(2^(n))));
    y1 = y + (x * d * (1/(2^(n))));
    x = x1;
    y = y1;
    z = z - (d * (180 / pi) * atan(1/(2^n)));
    k = k * (1 + (1 / (2^(2*n))));
end

x = (1 / sqrt(k)) * x;
y = (1 / sqrt(k)) * y;

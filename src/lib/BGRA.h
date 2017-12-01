#ifndef BGRA_H
#define BGRA_H

// A structure for a color.  Each channel is 8 bits [0-255].
struct BGRA {
    BGRA() : b(0), g(0), r(0), a(0) {}
    BGRA(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255)
        : b(blue), g(green), r(red), a(alpha) {}

    // C++ TIP:
    // A union struct. Essentially, this makes b <==> channels[0],
    // g <==> channels[1], etc. In other words: b, g, r, and a are
    // stored at the same memory location as channels[4]. Note that
    // sizeof(b)+sizeof(g)+sizeof(r)+sizeof(a) = sizeof(channels)
    // so the memory overlaps **exactly**.
    //
    // You might want to take advantage of union structs in later
    // assignments, although we don't require or expect you to do so.
    //

    union {
        struct { unsigned char b, g, r, a; };
        unsigned char channels[4];
    };

    BGRA operator+(const BGRA &c1) const;
    BGRA operator-(const BGRA &c1) const;
    BGRA operator*(const BGRA &c1) const;
    BGRA operator/(const BGRA &c1) const;

    friend bool operator==(const BGRA &c1, const BGRA &c2);
    friend bool operator!=(const BGRA &c1, const BGRA &c2);

};

#endif // BGRA_H

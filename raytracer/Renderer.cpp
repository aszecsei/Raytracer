#include "Renderer.h"
#include "stb_image_write.h"
#include "Ray.h"

double hit_sphere(const Point3& center, double radius, const Ray& r) {
    Vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        return (-half_b - std::sqrt(discriminant)) / a;
    }
}

Color ray_color(const Ray& r) {
    auto t = hit_sphere(Point3(0, 0, -1), 0.5, r);
    if (t > 0.0) {
        Vec3 normal = normalized(r.at(t) - Vec3(0, 0, -1));
        return 0.5 * Color(normal.x() + 1, normal.y() + 1, normal.z() + 1);
    }
    Vec3 unit_direction = normalized(r.direction());
    t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

void Renderer::generate_image()
{
    // Image

    m_image = Image(m_width, m_height);
    const auto aspect_ratio = (double)m_width / (double)m_height;

    // Camera

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = Point3(0, 0, 0);
    auto horizontal = Vec3(viewport_width, 0, 0);
    auto vertical = Vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focal_length);

    // Render

    for (int j = m_height - 1; j >= 0; --j)
    {
        for (int i = 0; i < m_width; ++i)
        {
            auto u = double(i) / (m_width - 1);
            auto v = double(j) / (m_height - 1);

            Ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
            Color pixel_color = ray_color(r);

            m_image.at(i, j) = ray_color(r);
        }
    }
}

void Renderer::write_to_image(const std::string_view& path)
{
    stbi_flip_vertically_on_write(true);
    stbi_write_png(path.data(), m_image.width(), m_image.height(), Color::CHANNELS, m_image.bytes().get(), m_width * Color::CHANNELS);
}
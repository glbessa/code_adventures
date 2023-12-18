const canvas = document.getElementById("universe");
const ctx = canvas.getContext('2d');

canvas.width = window.innerWidth;
canvas.height = window.innerHeight;

let celestial_bodies = [];

class CelestialBody {
    constructor(x, y, radius, ox, oy, o_radius, vel, color) {
        this.x = x;
        this.y = y;
        this.radius = radius;
        this.ox = ox;
        this.oy = oy;
        this.o_radius = o_radius;
        this.vel = vel;
        this.color = color;
    }

    draw() {
        ctx.beginPath();
        ctx.arc(this.x, this.y, this.radius, 0, Math.PI * 2);
        ctx.fillStyle = this.color;
        ctx.fill();
        ctx.closePath();
    }

    update() {
        
    }
}

function animate() {
    requestAnimationFrame(animate);
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    for (const cb of celestial_bodies) {
        cb.update();
        cb.draw();
    }
}

document.addEventListener("DOMContentLoaded", () => {
    celestial_bodies.push(new CelestialBody(canvas.width/2, canvas.height/2, 10, 0, 0, 0, `rgb(255, 0, 0)`));
    animate();
});
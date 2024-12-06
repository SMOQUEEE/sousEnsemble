document.addEventListener('DOMContentLoaded', () => {
    const bubbles = document.querySelectorAll('.bubble');
    
    bubbles.forEach(bubble => {
        // Random starting position and rotation
        const randomX = Math.random() * 40 - 20;
        const randomY = Math.random() * 40 - 20;
        const randomRotation = Math.random() * 20 - 10;
        bubble.style.transform = `translate(${randomX}px, ${randomY}px) rotate(${randomRotation}deg)`;
        
        // Add interactive movement on mousemove
        document.addEventListener('mousemove', (e) => {
            const mouseX = e.clientX / window.innerWidth - 0.5;
            const mouseY = e.clientY / window.innerHeight - 0.5;
            
            const rect = bubble.getBoundingClientRect();
            const bubbleX = rect.left + rect.width / 2;
            const bubbleY = rect.top + rect.height / 2;
            
            const deltaX = (e.clientX - bubbleX) * 0.02;
            const deltaY = (e.clientY - bubbleY) * 0.02;
            
            const distance = Math.sqrt(Math.pow(e.clientX - bubbleX, 2) + Math.pow(e.clientY - bubbleY, 2));
            const scale = Math.max(1, 1.1 - distance / 1000);
            
            bubble.style.transform = `translate(${randomX + deltaX}px, ${randomY + deltaY}px) rotate(${randomRotation}deg) scale(${scale})`;
        });
    });

    // Add parallax effect to background
    document.addEventListener('mousemove', (e) => {
        const moveX = (e.clientX / window.innerWidth - 0.5) * 20;
        const moveY = (e.clientY / window.innerHeight - 0.5) * 20;
        
        document.querySelector('#oceanVideo').style.transform = 
            `translate(calc(-50% + ${moveX}px), calc(-50% + ${moveY}px))`;
    });
});
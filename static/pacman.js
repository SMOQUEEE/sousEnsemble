class PacMan {
    constructor(canvas) {
        this.canvas = canvas;
        this.ctx = canvas.getContext('2d');
        this.tileSize = 16;
        this.score = 0;
        this.pacman = {
            x: 13,
            y: 23,
            direction: 0,
            mouthOpen: true
        };
        this.ghosts = [];
        this.dots = [];
        this.walls = [];
        this.gameLoop = null;

        // Références aux musiques
        this.gameMusic = document.getElementById('gameMusic');
        this.gameOverMusic = document.getElementById('gameOverMusic');

        this.setupGame();
    }

    setupGame() {
        this.createMaze();
        this.createGhosts();
        this.createDots();
        document.addEventListener('keydown', this.handleKeyPress.bind(this));
    }

    createMaze() {
        // Simplified maze layout
        const mazeLayout = [
            "WWWWWWWWWWWWWWWWWWWWWWWWWWWW",
            "W............WW............W",
            "W.WWWW.WWWW.WW.WWWW.WWWW.W.W",
            "W.WWWW.WWWW.WW.WWWW.WWWW.W.W",
            "W.WWWW.WWWW.WW.WWWW.WWWW.W.W",
            "W..........................W",
            "W.WWWW.WW.WWWWWW.WW.WWWW.W.W",
            "W.WWWW.WW.WWWWWW.WW.WWWW.W.W",
            "W......WW....WW....WW......W",
            "WW..WW.WWWWW WW WWWWW.WWWW.W",
            "W    W.WWWWW WW WWWWW.W   .W",
            "W    W.WW          WW.W   .W",
            "W    W.WW WWW--WWW WW.W   .W",
            "WW..WW.WW W      W WW.WWWW.W",
            "W     .................    W",
            "WW..WW.WW W      W WW.WWWWWW",
            "W    W.WW WWWW  WW WW.W   W.W",
            "W    W.WW          WW.W   W.W",
            "W    W.WW WWWW  WW WW.W   W.W",
            "WW..WW.WW WWWWWWWW WW.WWWWWW",
            "W............WW............W",
            "W.WWWW.WWWW.WW.WWWW.WWWW.W.W",
            "W.WWWW.WWWW.WW.WWWW.WWWW.W.W",
            "W...WW................WW...W",
            "WWW.WW.WW.WWWWWW.WW.WW.WWW.W",
            "WWW.WW.WW.WWWWWW.WW.WW.WWW.W",
            "W......WW....WW....WW......W",
            "W.WWWWWWWWWW.WW.WWWWWWWW.W.W",
            "W.WWWWWWWWWW.WW.WWWWWWWW.W.W",
            "W..........................W",
            "WWWWWWWWWWWWWWWWWWWWWWWWWWWW"
        ];
        mazeLayout.forEach((row, y) => {
            [...row].forEach((cell, x) => {
                if (cell === 'W') {
                    this.walls.push({x, y});
                }
            });
        });
    }

    createGhosts() {
        const ghostColors = ['#FF0000', '#00FFFF', '#FFB8FF', '#FFB852'];
        for (let i = 0; i < 4; i++) {
            this.ghosts.push({
                x: 14 + i,
                y: 14,
                direction: Math.floor(Math.random() * 4),
                color: ghostColors[i]
            });
        }
    }

    createDots() {
        for (let y = 0; y < 31; y++) {
            for (let x = 0; x < 28; x++) {
                if (!this.walls.some(wall => wall.x === x && wall.y === y)) {
                    this.dots.push({x, y});
                }
            }
        }
    }

    handleKeyPress(e) {
        const directions = {
            'ArrowLeft': 2,
            'ArrowRight': 0,
            'ArrowUp': 3,
            'ArrowDown': 1
        };

        if (directions.hasOwnProperty(e.key)) {
            this.pacman.direction = directions[e.key];
        }
    }

    update() {
        this.movePacman();
        this.moveGhosts();
        this.checkCollisions();
        this.draw();
    }

    movePacman() {
        const directions = [
            {x: 1, y: 0},
            {x: 0, y: 1},
            {x: -1, y: 0},
            {x: 0, y: -1}
        ];

        const dir = directions[this.pacman.direction];
        const newX = this.pacman.x + dir.x;
        const newY = this.pacman.y + dir.y;

        if (!this.walls.some(wall => wall.x === newX && wall.y === newY)) {
            this.pacman.x = newX;
            this.pacman.y = newY;
        }
    }

    moveGhosts() {
        this.ghosts.forEach(ghost => {
            const directions = [
                {x: 1, y: 0},
                {x: 0, y: 1},
                {x: -1, y: 0},
                {x: 0, y: -1}
            ];

            const dir = directions[ghost.direction];
            const newX = ghost.x + dir.x;
            const newY = ghost.y + dir.y;

            if (!this.walls.some(wall => wall.x === newX && wall.y === newY)) {
                ghost.x = newX;
                ghost.y = newY;
            } else {
                ghost.direction = Math.floor(Math.random() * 4);
            }
        });
    }

    checkCollisions() {
        this.dots = this.dots.filter(dot => {
            if (dot.x === this.pacman.x && dot.y === this.pacman.y) {
                this.score += 10;
                return false;
            }
            return true;
        });

        this.ghosts.forEach(ghost => {
            if (ghost.x === this.pacman.x && ghost.y === this.pacman.y) {
                this.gameOver();
            }
        });

        if (this.dots.length === 0) {
            this.gameWon();
        }
    }

    draw() {
        this.ctx.fillStyle = '#000';
        this.ctx.fillRect(0, 0, this.canvas.width, this.canvas.height);

        this.ctx.fillStyle = '#00F';
        this.walls.forEach(wall => {
            this.ctx.fillRect(
                wall.x * this.tileSize,
                wall.y * this.tileSize,
                this.tileSize,
                this.tileSize
            );
        });

        this.ctx.fillStyle = '#FFF';
        this.dots.forEach(dot => {
            this.ctx.beginPath();
            this.ctx.arc(
                dot.x * this.tileSize + this.tileSize / 2,
                dot.y * this.tileSize + this.tileSize / 2,
                2,
                0,
                Math.PI * 2
            );
            this.ctx.fill();
        });

        this.ctx.fillStyle = '#FF0';
        this.ctx.beginPath();
        const pacX = this.pacman.x * this.tileSize + this.tileSize / 2;
        const pacY = this.pacman.y * this.tileSize + this.tileSize / 2;
        this.ctx.arc(pacX, pacY, this.tileSize / 2, 0, Math.PI * 2);
        this.ctx.fill();

        this.ghosts.forEach(ghost => {
            this.ctx.fillStyle = ghost.color;
            this.ctx.beginPath();
            const ghostX = ghost.x * this.tileSize + this.tileSize / 2;
            const ghostY = ghost.y * this.tileSize + this.tileSize / 2;
            this.ctx.arc(ghostX, ghostY, this.tileSize / 2, 0, Math.PI * 2);
            this.ctx.fill();
        });

        document.getElementById('score').textContent = `Score: ${this.score}`;
    }

    gameOver() {
        clearInterval(this.gameLoop);
        this.gameMusic.pause();
        this.gameMusic.currentTime = 0;
        this.gameOverMusic.play();
        setTimeout(() => {
            alert('Game Over! \n Fin de l aventure.... \n Merci de votre participation');
            this.setupGame();
        }, 500);
    }

    gameWon() {
        clearInterval(this.gameLoop);
        alert('Congratulations! You won!');
        this.setupGame();
    }

    start() {
        if (this.gameLoop) {
            clearInterval(this.gameLoop);
        }
        this.gameMusic.play();
        this.gameLoop = setInterval(() => this.update(), 100);
    }
}

document.addEventListener('DOMContentLoaded', () => {
    const canvas = document.getElementById('gameCanvas');
    const game = new PacMan(canvas);

    document.getElementById('startButton').addEventListener('click', () => {
        game.start();
    });
});

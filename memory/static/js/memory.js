let cards = [];
let flippedCards = [];
let matchedPairs = 0;
let timer;
let timeLeft = 60;
let isGameActive = false;

const cardImages = [
    'card1.png', 'card1.png',
    'card2.png', 'card2.png',
    'card3.png', 'card3.png',
    'card4.png', 'card4.png',
    'card5.png', 'card5.png',
    'card6.png', 'card6.png'
];

const sounds = {
    flip: new Audio('/static/sounds/flip.mp3'),
    match: new Audio('/static/sounds/match.mp3'),
    victory: new Audio('/static/sounds/victory.mp3'),
    gameOver: new Audio('/static/sounds/gameover.mp3')
};

function shuffleCards() {
    return cardImages.sort(() => Math.random() - 0.5);
}

function startGame() {
    if (isGameActive) return;
    
    isGameActive = true;
    matchedPairs = 0;
    flippedCards = [];
    timeLeft = 60;
    
    const shuffledCards = shuffleCards();
    const gameBoard = document.querySelector('.game-board');
    gameBoard.innerHTML = '';
    
    shuffledCards.forEach((img, index) => {
        const card = document.createElement('div');
        card.className = 'card';
        card.dataset.cardIndex = index;
        card.innerHTML = `
            <div class="card-inner">
                <div class="card-front"></div>
                <div class="card-back" style="background-image: url('/static/images/${img}')"></div>
            </div>
        `;
        card.addEventListener('click', flipCard);
        gameBoard.appendChild(card);
    });
    
    startTimer();
    document.querySelector('.start-button').style.display = 'none';
}

function flipCard() {
    if (!isGameActive || flippedCards.length >= 2 || this.classList.contains('flipped')) return;
    
    sounds.flip.play();
    this.classList.add('flipped');
    flippedCards.push(this);
    
    if (flippedCards.length === 2) {
        checkMatch();
    }
}

function checkMatch() {
    const [card1, card2] = flippedCards;
    const match = card1.querySelector('.card-back').style.backgroundImage === 
                 card2.querySelector('.card-back').style.backgroundImage;
    
    if (match) {
        sounds.match.play();
        matchedPairs++;
        flippedCards = [];
        
        if (matchedPairs === 6) {
            victory();
        }
    } else {
        setTimeout(() => {
            card1.classList.remove('flipped');
            card2.classList.remove('flipped');
            flippedCards = [];
        }, 1000);
    }
}

function startTimer() {
    timer = setInterval(() => {
        timeLeft--;
        document.querySelector('.timer').textContent = timeLeft;
        
        if (timeLeft <= 0) {
            gameOver();
        }
    }, 1000);
}

function victory() {
    isGameActive = false;
    clearInterval(timer);
    sounds.victory.play();
    document.querySelector('.victory-screen').style.display = 'flex';
    createFireworks();
}

function gameOver() {
    isGameActive = false;
    clearInterval(timer);
    sounds.gameOver.play();
    document.querySelector('.game-over-screen').style.display = 'flex';
    document.body.classList.add('game-over');
}

function createFireworks() {
    for (let i = 0; i < 10; i++) {
        setTimeout(() => {
            const firework = document.createElement('div');
            firework.className = 'firework';
            firework.style.left = Math.random() * 100 + 'vw';
            document.querySelector('.victory-screen').appendChild(firework);
            
            setTimeout(() => firework.remove(), 1000);
        }, i * 300);
    }
}

function resetGame() {
    document.querySelector('.victory-screen').style.display = 'none';
    document.querySelector('.game-over-screen').style.display = 'none';
    document.body.classList.remove('game-over');
    document.querySelector('.start-button').style.display = 'block';
    document.querySelector('.timer').textContent = '60';
}
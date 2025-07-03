<nav class="navbar">
  <div class="navbar-content">
    <span class="logo">PentaLedger</span>
    <ul class="nav-links">
      <li><a href="/">Home</a></li>
      <li><a href="/features">Features</a></li>
      <li><a href="/profile">Profile</a></li>
    </ul>
  </div>
</nav>

<style>
.navbar {
  position: fixed;
  top: 0;
  left: 0;
  width: 100vw;
  height: 60px;
  background: #111;
  color: #fff;
  display: flex;
  align-items: center;
  z-index: 1000;
  box-shadow: 0 2px 8px rgba(0,0,0,0.08);
}
.navbar-content {
  width: 100%;
  display: flex;
  align-items: center;
  justify-content: space-between;
  padding: 0 2rem;
}
.logo {
  font-weight: bold;
  font-size: 1.3rem;
}
.nav-links {
  list-style: none;
  display: flex;
  gap: 1.5rem;
  margin: 0;
  padding: 0;
}
.nav-links li a {
  color: #fff;
  text-decoration: none;
  font-size: 1rem;
  transition: color 0.2s;
}
.nav-links li a:hover {
  color: #ffd700;
}
</style> 
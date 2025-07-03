<script>
// Sidebar logic can go here if needed
</script>

<aside class="sidebar">
  <nav>
    <ul>
      <li><a href="/">Home</a></li>
      <li><a href="/governance">Governance</a></li>
      <li><a href="/vehicles">Vehicles & Mileage</a></li>
      <li><a href="/settings">Settings</a></li>
    </ul>
  </nav>
</aside>

<style>
.sidebar {
  width: 220px;
  height: 100vh;
  background: #222;
  color: #fff;
  padding: 1rem 0;
  position: fixed;
  top: 0;
  left: 0;
  display: flex;
  flex-direction: column;
}
.sidebar nav ul {
  list-style: none;
  padding: 0;
  margin: 0;
}
.sidebar nav ul li {
  margin: 1rem 0;
}
.sidebar nav ul li a {
  color: #fff;
  text-decoration: none;
  padding: 0.5rem 1.5rem;
  display: block;
  border-radius: 4px;
  transition: background 0.2s;
}
.sidebar nav ul li a:hover {
  background: #444;
}
</style> 
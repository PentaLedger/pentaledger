<script>
  let email = '';
  let password = '';
  let isLoading = false;

  function handleLogin() {
    isLoading = true;
    // TODO: Implement actual login logic
    console.log('Login attempt:', { email, password });
    
    // Simulate login process
    setTimeout(() => {
      isLoading = false;
      // Redirect to dashboard after successful login
      window.location.href = '/';
    }, 1000);
  }
</script>

<div class="login-container">
  <div class="login-card">
    <div class="login-header">
      <h1>Welcome to PentaLedger</h1>
      <p>Sign in to your account</p>
    </div>
    
    <form class="login-form" on:submit|preventDefault={handleLogin}>
      <div class="form-group">
        <label for="email">Email</label>
        <input 
          type="email" 
          id="email" 
          bind:value={email} 
          placeholder="Enter your email"
          required
        />
      </div>
      
      <div class="form-group">
        <label for="password">Password</label>
        <input 
          type="password" 
          id="password" 
          bind:value={password} 
          placeholder="Enter your password"
          required
        />
      </div>
      
      <div class="form-options">
        <label class="checkbox-label">
          <input type="checkbox" />
          <span>Remember me</span>
        </label>
        <a href="/forgot-password" class="forgot-link">Forgot password?</a>
      </div>
      
      <button type="submit" class="login-button" disabled={isLoading}>
        {isLoading ? 'Signing in...' : 'Sign In'}
      </button>
    </form>
    
    <div class="login-footer">
      <p>Don't have an account? <a href="/register">Sign up</a></p>
    </div>
  </div>
</div>

<style>
  .login-container {
    min-height: 100vh;
    display: flex;
    align-items: center;
    justify-content: center;
    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
    padding: 2rem;
  }
  
  .login-card {
    background: white;
    border-radius: 12px;
    box-shadow: 0 10px 25px rgba(0, 0, 0, 0.1);
    padding: 3rem;
    width: 100%;
    max-width: 400px;
  }
  
  .login-header {
    text-align: center;
    margin-bottom: 2rem;
  }
  
  .login-header h1 {
    font-size: 1.75rem;
    color: #333;
    margin-bottom: 0.5rem;
  }
  
  .login-header p {
    color: #666;
    font-size: 0.95rem;
  }
  
  .login-form {
    display: flex;
    flex-direction: column;
    gap: 1.5rem;
  }
  
  .form-group {
    display: flex;
    flex-direction: column;
    gap: 0.5rem;
  }
  
  .form-group label {
    font-weight: 500;
    color: #333;
    font-size: 0.9rem;
  }
  
  .form-group input {
    padding: 0.75rem;
    border: 1px solid #ddd;
    border-radius: 6px;
    font-size: 1rem;
    transition: border-color 0.2s;
  }
  
  .form-group input:focus {
    outline: none;
    border-color: #667eea;
    box-shadow: 0 0 0 3px rgba(102, 126, 234, 0.1);
  }
  
  .form-options {
    display: flex;
    justify-content: space-between;
    align-items: center;
    font-size: 0.9rem;
  }
  
  .checkbox-label {
    display: flex;
    align-items: center;
    gap: 0.5rem;
    color: #666;
    cursor: pointer;
  }
  
  .checkbox-label input[type="checkbox"] {
    margin: 0;
  }
  
  .forgot-link {
    color: #667eea;
    text-decoration: none;
  }
  
  .forgot-link:hover {
    text-decoration: underline;
  }
  
  .login-button {
    background: #667eea;
    color: white;
    border: none;
    padding: 0.75rem;
    border-radius: 6px;
    font-size: 1rem;
    font-weight: 500;
    cursor: pointer;
    transition: background-color 0.2s;
  }
  
  .login-button:hover:not(:disabled) {
    background: #5a6fd8;
  }
  
  .login-button:disabled {
    background: #ccc;
    cursor: not-allowed;
  }
  
  .login-footer {
    text-align: center;
    margin-top: 2rem;
    padding-top: 1.5rem;
    border-top: 1px solid #eee;
    color: #666;
    font-size: 0.9rem;
  }
  
  .login-footer a {
    color: #667eea;
    text-decoration: none;
  }
  
  .login-footer a:hover {
    text-decoration: underline;
  }
</style> 
<script>
  import { login } from '$lib/auth';
  import { goto } from '$app/navigation';
  
  let email = '';
  let password = '';
  let errorMessage = '';
  let isLoading = false;

  async function handleLogin() {
    isLoading = true;
    errorMessage = '';
    
    const result = await login(email, password);
    
    if (result.success) {
      // Redirect to dashboard after successful login
      goto('/');
    } else {
      errorMessage = result.error || 'Login failed. Please try again.';
      isLoading = false;
    }
  }
</script>

<div class="login-container">
  <div class="login-card">
    <div class="login-header">
      <h1>Welcome to PentaLedger</h1>
      <p>Sign in to your account</p>
    </div>
    
    {#if errorMessage}
      <div class="error-message">
        {errorMessage}
      </div>
    {/if}
    
    <form class="login-form" on:submit|preventDefault={handleLogin}>
      <div class="form-group">
        <label for="email">Email</label>
        <input 
          type="email" 
          id="email" 
          bind:value={email} 
          placeholder="Enter your email"
          required
          disabled={isLoading}
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
          disabled={isLoading}
        />
      </div>
      
      <div class="form-options">
        <label class="checkbox-label">
          <input type="checkbox" disabled={isLoading} />
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
    
    <div class="demo-credentials">
      <p><strong>Demo Credentials:</strong></p>
      <p>Admin: admin@pentaledger.com / admin123</p>
      <p>User: user@pentaledger.com / user123</p>
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
  
  .error-message {
    background: #fee;
    color: #c33;
    padding: 0.75rem;
    border-radius: 6px;
    margin-bottom: 1.5rem;
    font-size: 0.9rem;
    border: 1px solid #fcc;
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
  
  .form-group input:disabled {
    background: #f5f5f5;
    cursor: not-allowed;
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
  
  .demo-credentials {
    margin-top: 2rem;
    padding: 1rem;
    background: #f8f9fa;
    border-radius: 6px;
    font-size: 0.8rem;
    color: #666;
  }
  
  .demo-credentials p {
    margin: 0.25rem 0;
  }
  
  .demo-credentials strong {
    color: #333;
  }
</style> 